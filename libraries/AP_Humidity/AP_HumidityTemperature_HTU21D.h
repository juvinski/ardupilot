/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AP_HumidityTemperature_HTU21D.h
 * Author: juvinski
 *
 * Created on April 18, 2017, 2:53 PM
 */
#include "AP_Humidity.h"
#include "HumidityTemperature.h"
#include "HumidityTemperature_Backend.h"
#include <AP_HAL/I2CDevice.h>
#include <utility>
#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <AP_Param/AP_Param.h>
#include <GCS_MAVLink/GCS_MAVLink.h>
#include <GCS_MAVLink/GCS.h>

class AP_HumidityTemperature_HTU21D : public AP_HumidityTemperature_Backend
{
public:
    AP_HumidityTemperature_HTU21D(AP_HumidityTemperature &_humiditytemperature);
    ~AP_HumidityTemperature_HTU21D();

    void init(void);
    void read(void);
    
    float getTemperature(void);
    float getHumidity(void);
    
private:
    float _humidity;
    float _temperature;
    AP_HAL::OwnPtr<AP_HAL::I2CDevice> _dev;
    bool _dev_alive=false;
    uint8_t _resolution;
    int crc_check(const uint8_t *buf, int len);
    void readTemperature();
    void readHumidity();
};