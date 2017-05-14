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

const AP_Param::GroupInfo AP_HumidityTemperature::var_info[] = 
{
    // @Param: ENABLE
    // @DisplayName: Enable or disable Humidity and Temperature sensor
    // @Description: If you have the HTU21D connected at IC2 You can enable this to generated at Dataflash Log Temperature and Humidity
    // @Values: 0:Disable,1:Enable
    // @User: Advanced
    AP_GROUPINFO("ENABLE", 0, AP_HumidityTemperature, _enable, 0),
    
    AP_GROUPEND
};

AP_HumidityTemperature::AP_HumidityTemperature()
{
    AP_Param::setup_object_defaults(this, var_info);
    driver = new AP_HumidityTemperature_HTU21D(*this);
            
}
/*
  initialise the Humidity class. 
 */
void AP_HumidityTemperature::init(void)
{
    driver->init();
}

void AP_HumidityTemperature::read(void)
{
    if(!_enable)
    {
        //GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, "SEM PARADA");
        enabled = false;
        return;
    }
    else
    {
        //GCS_MAVLINK::send_statustext_all(MAV_SEVERITY_CRITICAL, "COM PARADA");
        enabled = true;
        driver->read();
    }
}

float AP_HumidityTemperature::getHumidity(void)
{
    if(!_enable)
    {
        return 0;
    }
    else
    {
        return driver->getHumidity();
    }
}

float AP_HumidityTemperature::getTemperature() 
{
    if(!_enable)
    {
        return 0;
    }
    else
    {
        return driver->getTemperature();
    }
}