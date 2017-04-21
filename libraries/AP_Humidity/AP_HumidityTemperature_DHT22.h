/*
 DHT22 Sensor Driver - A driver to read Temperature and Humidity from DHT22 Sensor
*/
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

#pragma once
#include <AP_HAL/AP_HAL.h>
#include <stdio.h>
#include <unistd.h>
#include <AP_Param/AP_Param.h>
#include "AP_Humidity.h"
#include "HumidityTemperature.h"
#include "HumidityTemperature_Backend.h"

#if CONFIG_HAL_BOARD == HAL_BOARD_VRBRAIN
 # define DHT_PIN    0
#elif CONFIG_HAL_BOARD == HAL_BOARD_LINUX && CONFIG_HAL_BOARD_SUBTYPE == HAL_BOARD_SUBTYPE_LINUX_BBBMINI
 # define DHT_PIN   27 // GPIO P8_16
#else
 # define DHT_PIN     0 // pin undefined on other boards
#endif

 #define DHT_MAXCOUNT 64000
 #define DHT_PULSES 41

class AP_HumidityTemperature_DHT22 : public AP_HumidityTemperature_Backend
{
public:
    //Constructor
    AP_HumidityTemperature_DHT22(AP_HumidityTemperature &_humiditytemperature);
    
    //Init method
    void init(void);
    
    //Destructor
    ~AP_HumidityTemperature_DHT22();
    
    //read method
    void read(void);
    
    float getTemperature(void);
    float getHumidity(void);
    
private:
    float _humidity;
    float _temperature;
};