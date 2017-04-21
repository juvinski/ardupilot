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

#include <AP_HAL/AP_HAL.h>
#include <inttypes.h>
#include <AP_Common/AP_Common.h>
#include <AP_Param/AP_Param.h>
#include <AP_Vehicle/AP_Vehicle.h>
#include "AP_Humidity.h"
#include "HumidityTemperature.h"

class AP_HumidityTemperature_Backend
{
public:
    // constructor
    AP_HumidityTemperature_Backend(AP_HumidityTemperature &_humiditytemperature);
    
    // we declare a virtual destructor so that  drivers can
    // override with a custom destructor if need be
    virtual ~AP_HumidityTemperature_Backend(void) {}
    
    /// Startup initialisation.
    virtual void init(void) = 0;
    
    virtual void read(void) = 0;

    virtual float getTemperature(void) = 0;
    
    virtual float getHumidity(void) = 0;
    
private:
    AP_HumidityTemperature &humiditytemperature;
};