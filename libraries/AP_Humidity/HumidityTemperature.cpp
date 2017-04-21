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

#include "HumidityTemperature.h"
#include "HumidityTemperature_Backend.h"
#include "AP_HumidityTemperature_DHT22.h"
#include "AP_HumidityTemperature_HTU21D.h"

extern const AP_HAL::HAL &hal;

AP_HumidityTemperature::AP_HumidityTemperature()
{
    //memset(driver,0,sizeof(driver));
    //driver = new AP_HumidityTemperature_DHT22(*this);
    driver = new AP_HumidityTemperature_HTU21D(*this);
            
}
/*
  initialise the Humidity class. 
 */
void AP_HumidityTemperature::init(void)
{
    //driver = new AP_HumidityTemperature_DHT22(*this);
    driver->init();
}

/*
  update RangeFinder state for all instances. This should be called at
  around 10Hz by main loop
 */
void AP_HumidityTemperature::read(void)
{
    driver->read();
}

float AP_HumidityTemperature::getHumidity(void)
{
    return driver->getHumidity();
}

float AP_HumidityTemperature::getTemperature() 
{
    return driver->getTemperature();
}
