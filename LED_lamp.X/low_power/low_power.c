#include <pic.h> 
#include "low_power.h"

void Enter_Low_Power_Mode( low_power_mode_t mode )
{
    switch (mode)
    {
    case SLEEP_MODE:
        VREGCONbits.VREGPM = 1;
        SLEEP();
        break;
    default:
        break;
    }
    
}