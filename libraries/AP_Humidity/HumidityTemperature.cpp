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
#include "DHT22.h"

extern const AP_HAL::HAL &hal;

Humidity::Humidity(DataFlash_Class *dataflash)
{
    AP_Param::setup_object_defaults(this, var_info);
    memset(drivers,0,sizeof(drivers));
}

/*
  initialise the Humidity class. 
 */
void Humidity::init(void)
{
    
}

/*
  update RangeFinder state for all instances. This should be called at
  around 10Hz by main loop
 */
void Humidity::read(void)
{

}