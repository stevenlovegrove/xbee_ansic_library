#include <Arduino.h>
#include <time.h>
#include <xbee/platform.h>

uint32_t xbee_seconds_timer()
{
    // This will have bad overflow behavour, but let's see what happens.
    return xbee_millisecond_timer()/1000;
}

uint32_t xbee_millisecond_timer()
{
    return millis();
}
