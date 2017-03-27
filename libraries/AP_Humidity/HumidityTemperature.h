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
#pragma once

#include <AP_Common/AP_Common.h>
#include <AP_HAL/AP_HAL.h>
#include <AP_Param/AP_Param.h>
#include <AP_Math/AP_Math.h>
#include <inttypes.h>
#include <AP_Vehicle/AP_Vehicle.h>
//#include "HumidityTemperature_Backend.h"

class AP_HumidityTemperature_Backend; 

class AP_HumidityTemperature
{
public:
    friend class AP_HumidityTemperature_Backend;

    AP_HumidityTemperature();
    
    // initialise humidity sensor
    void init(void);

    // read humidity value and store in the dataflash log
    // Update just can be run at least 2 seconds
    void read(void);
    
    float getTemperature(void);
    float getHumidity(void);
    
private:
    AP_HumidityTemperature_Backend *driver;
    float _humidity;
    float _temperature;
};