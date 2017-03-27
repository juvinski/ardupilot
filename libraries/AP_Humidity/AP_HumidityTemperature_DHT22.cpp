// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
/*
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <utility>
#include <AP_HAL/AP_HAL.h>
#include <time.h>
#include "AP_HumidityTemperature_DHT22.h"
#include <GCS_MAVLink/GCS_MAVLink.h>
#include <GCS_MAVLink/GCS.h>

extern const AP_HAL::HAL& hal;

AP_HumidityTemperature_DHT22::AP_HumidityTemperature_DHT22(AP_HumidityTemperature &_humiditytemperature) :
AP_HumidityTemperature_Backend(_humiditytemperature)
{
}

AP_HumidityTemperature_DHT22::~AP_HumidityTemperature_DHT22()
{
    
}

void AP_HumidityTemperature_DHT22::init()
{
    //PIN DHT_PIN
    _humidity = 0.0f;
    _temperature = 0.0f;
}

void AP_HumidityTemperature_DHT22::read() 
{
    _humidity = 0.0f;
    _temperature = 0.0f;
    
    hal.console->printf( "read start\n");
    
     int pulseCounts[DHT_PULSES*2] = {0};
    
    //Waking up sensor
    hal.gpio->pinMode(DHT_PIN,HAL_GPIO_OUTPUT);
    hal.gpio->write(DHT_PIN,1);
    usleep(500000);
    hal.gpio->write(DHT_PIN,0);
    usleep(20000);
        
    //Waiting data
    hal.console->printf( "waiting data\n");
    hal.gpio->pinMode(DHT_PIN,HAL_GPIO_INPUT);

    while (hal.gpio->read(DHT_PIN))
    {
        usleep(1);
    }

    hal.console->printf( "reading\n");
    // Record pulse widths for the expected result bits
    for (int i=0; i < DHT_PULSES*2; i+=2)
    {
        // Count how long pin is low and store in pulseCounts[i]
        while (hal.gpio->read(DHT_PIN)==0)
        {
            if (++pulseCounts[i] >= DHT_MAXCOUNT) 
            {
                _humidity = -666;
                _temperature = -666;
                hal.console->printf( "0 Humidity = %.1f %% Temperature = %.1f *C\n", _humidity, _temperature );
                GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, "0 Sensor Humidity: %.1f %% - Temperature: %.1f *C\n", _humidity, _temperature);
                return;
            }
        }
        // Count how long pin is high and store in pulseCounts[i+1]
        while (hal.gpio->read(DHT_PIN)==1) 
        {
            if (++pulseCounts[i+1] >= DHT_MAXCOUNT*8) 
            {
                _humidity = -666;
                _temperature = -666;
                hal.console->printf( "1 Humidity = %.1f %% Temperature = %.1f *C\n", _humidity, _temperature );
                GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, "1 Sensor Humidity: %.1f %% - Temperature: %.1f *C\n", _humidity, _temperature);
                return;
            }
        }
    }
    hal.console->printf( "pulsing\n");
    int threshold = 0;
    for (int i=2; i < DHT_PULSES*2; i+=2) 
    {
        threshold += pulseCounts[i];
    }
    threshold /= DHT_PULSES-1;
    
    uint8_t data[5] = {0};
    for (int i=3; i < DHT_PULSES*2; i+=2) 
    {
        int index = (i-3)/16;
        data[index] <<= 1;
        if (pulseCounts[i] >= threshold) 
        {
            data[index] |= 1;
        }
    }

    hal.console->printf( "checksum\n");
    // Verify checksum of received data.
    if (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)) 
    {
        /*if (type == DHT11) 
        {
            // Get humidity and temp for DHT11 sensor.
            *humidity = (float)data[0];
            *temperature = (float)data[2];
        }
        else if (type == DHT22) { */
        // Calculate humidity and temp for DHT22 sensor.
        _humidity = (data[0] * 256 + data[1]) / 10.0f;
        _temperature = ((data[2] & 0x7F) * 256 + data[3]) / 10.0f;
        if (data[2] & 0x80) 
        {
            _temperature *= -1.0f;
        }
        hal.console->printf( "Humidity = %.1f %% Temperature = %.1f *C\n", _humidity, _temperature );
        GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, "Sensor Humidity: %.1f %% - Temperature: %.1f *C\n", _humidity, _temperature);
    }
    else 
    {
        _humidity = -99;
        _temperature = -99;
    }
}
float AP_HumidityTemperature_DHT22::getTemperature()
{
    return _temperature;
}

float AP_HumidityTemperature_DHT22::getHumidity()
{
    return _humidity;
}