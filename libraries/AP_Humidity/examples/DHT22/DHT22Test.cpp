/*
 DHT22 Test
 */

#include <AP_HAL/AP_HAL.h>
#include <AP_Humidity/AP_Humidity.h>

const AP_HAL::HAL& hal = AP_HAL::get_HAL();

static AP_HumidityTemperature humidity;

static uint32_t timer;
static uint8_t counter;

void setup()
{
    hal.console->println("Humidity library test");
    humidity.init();
}

void loop()
{
    hal.scheduler->delay(2000);
    humidity.read();
}

AP_HAL_MAIN();