/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AP_HumidityTemperature_HTU21D.cpp
 * Author: juvinski
 * 
 * Created on April 18, 2017, 2:53 PM
 */

#include "AP_HumidityTemperature_HTU21D.h"
#define HTU21D_I2C_BUS              2
#define HTU21D_I2C_ADDR             0x40

uint8_t HTU21DF_I2C_READTEMP_NOHOLD = 0xF3;
uint8_t HTU21DF_I2C_READHUM_NOHOLD = 0xF5;

const uint8_t HTU21DF_I2C_READREG = 0xE7;
const uint8_t HTU21DF_I2C_RESET = 0xFE;

#define ERROR_I2C_TIMEOUT 	998
#define ERROR_BAD_CRC		999

extern const AP_HAL::HAL &hal;

AP_HumidityTemperature_HTU21D::AP_HumidityTemperature_HTU21D(AP_HumidityTemperature &_humiditytemperature) : AP_HumidityTemperature_Backend(_humiditytemperature)
{
}

AP_HumidityTemperature_HTU21D::~AP_HumidityTemperature_HTU21D() 
{
}

void AP_HumidityTemperature_HTU21D::init()
{
    uint8_t buf[32];
    _humidity = 0.0f;
    _temperature = 0.0f;
    _dev = std::move(hal.i2c_mgr->get_device(HTU21D_I2C_BUS, HTU21D_I2C_ADDR)); 
    // take i2c bus sempahore
    if (!_dev || !_dev->get_semaphore()->take(1)) 
    {
        hal.console->printf( "HTU21D: Semaphore false\n");
        //GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL,"HTU21D: Semaphore false");
        _dev_alive = false;
    }
    else
    {
        //GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL,"RESET");
        uint8_t transaction[] = {HTU21DF_I2C_RESET};
        if(!_dev->transfer(transaction,sizeof(transaction),nullptr,0))
        {
            hal.console->println("HTU21D: Cannot reset!");
            _dev_alive = false;
        }
        else
        {
            //hal.scheduler->delay(15);
            usleep(15000);

            uint8_t tmp_Reset[] = {HTU21DF_I2C_READREG};
            if(!_dev->transfer(tmp_Reset,sizeof(tmp_Reset),nullptr,0))
            {
                hal.console->println("HTU21D: Cannot read user data!");
                _dev_alive = false;
            }
            else
            {
                _dev->read(buf,sizeof(buf));
                if (buf[0] != 0x02) 
                {
                    hal.console->println("HTU21D: Reset fail!");
                    _dev_alive = false;
                }
                else
                {
                    hal.console->println("HTU21D: Reset Ok!");
                    _dev_alive = true;
                }
            }
        }
    }
    _dev->get_semaphore()->give();
}

void AP_HumidityTemperature_HTU21D::read() 
{
    _temperature = 0.0f;
    _humidity = 0.0f;
    if(_dev_alive)
    {
        readTemperature();
        readHumidity();
        GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, "0 H: %.2f %% - T: %.2f *C\n", _humidity, _temperature);
    }
}

void AP_HumidityTemperature_HTU21D::readTemperature() 
{
    uint8_t rawTemperature[32];
    uint16_t tempRead;
    
    _temperature = 0.0f;
    //GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, "2 H: %.2f %% - T: %.2f *C\n", _humidity, _temperature);
    if (!_dev || !_dev->get_semaphore()->take(1)) 
    {
        hal.console->println("HTU21D Temperature: Unable to get semaphore!");
        _temperature = 0.0f;
    }
    
    uint8_t arrRead[] = {HTU21DF_I2C_READTEMP_NOHOLD}; 
    if(!_dev->transfer(arrRead,sizeof(arrRead),nullptr,0))
    {
        hal.console->println("HTU21D Temperature: Bad write!");
        _temperature = 0.0f;
    }
    //hal.scheduler->delay(50);
    usleep(50000);
    if(!_dev->read(rawTemperature,sizeof(rawTemperature)))
    {
        hal.console->println("HTU21D Temperature: Bad read!");
        _temperature = 0.0f;
    }
    else
    {
        if (crc_check(rawTemperature, 3) != 0) 
        {
            hal.console->println("HTU21D Temperature: I2C Bad CRC!");
            _temperature = 0.0f;
        }
        else
        {
            tempRead = ((rawTemperature[0] << 8) | rawTemperature[1]) & 0xFFFC;
            if(tempRead == ERROR_I2C_TIMEOUT)
            {
                hal.console->println("HTU21D Temperature: I2C Timeout!");
                _temperature = 0.0f;
            }
            else if (tempRead == ERROR_BAD_CRC)
            {
                hal.console->println("HTU21D Temperature: BAD CRC!");
                _temperature = 0.0f;
            }
            else
            {
                _temperature = ((tempRead / 65536.0) * 175.72) - 46.85;
            }
        }
    }
    _dev->get_semaphore()->give();
}

void AP_HumidityTemperature_HTU21D::readHumidity() 
{
    uint8_t rawHumidity[32];
    uint16_t humRead;
    //GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, "3 H: %.2f %% - T: %.2f *C\n", _humidity, _temperature);
    _humidity = 0.0f;

    if (!_dev || !_dev->get_semaphore()->take(HAL_SEMAPHORE_BLOCK_FOREVER)) 
    {
        AP_HAL::panic("HTU21D Humidity: Unable to get semaphore!");
        _humidity = 0.0f;
    }
    
    uint8_t arrRead[] = {HTU21DF_I2C_READHUM_NOHOLD}; 
    if(!_dev->transfer(arrRead,sizeof(arrRead),nullptr,0))
    {
        hal.console->println("HTU21D Humidity: Bad write!");
        _humidity = 0.0f;
    }
    //hal.scheduler->delay(16);
    usleep(16000);
    if(!_dev->read(rawHumidity,sizeof(rawHumidity)))
    {
        hal.console->println("HTU21D Humidity: Bad read!");
        _humidity = 0.0f;
    }
    else
    {
        if (crc_check(rawHumidity, 3) != 0) 
        {
            hal.console->println("HTU21D Humidity: I2C Bad CRC!");
            _humidity = 0.0f;
        }
        else
        {
            humRead = ((rawHumidity[0] << 8) | rawHumidity[1]) & 0xFFFC;
            if(humRead == ERROR_I2C_TIMEOUT)
            {
                hal.console->println("HTU21D Humidity: I2C Timeout!");
                _humidity = 0.0f;
            }
            else if (humRead == ERROR_BAD_CRC)
            {
                hal.console->println("HTU21D Humidity: BAD CRC!");
                _humidity = 0.0f;
            }
            else
            {
                _humidity = ((humRead / 65536.0) * 125.0) - 6.0;
            }
        }
    }
    _dev->get_semaphore()->give();
}


float AP_HumidityTemperature_HTU21D::getHumidity() 
{
    return _humidity;
}

float AP_HumidityTemperature_HTU21D::getTemperature() 
{
    return _temperature;
}

int AP_HumidityTemperature_HTU21D::crc_check(const uint8_t* buf, int len) 
{
    uint32_t dataandcrc;
    const uint32_t poly = 0x98800000;
    int i;

    if (len != 3) return -1;
    if (buf == NULL) return -1;

    dataandcrc = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8);
    for (i = 0; i < 24; i++) {
        if (dataandcrc & 0x80000000UL)
            dataandcrc ^= poly;
        dataandcrc <<= 1;
    }
    return (dataandcrc != 0);
}
