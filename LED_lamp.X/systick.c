/**
@brief Systick implementation source file.
   
This source file provides implementation for time counting for timed events. 
  
@file systick.c
@author Joao P Bino
*/

/**
  @section Included Files
*/
#include "systick.h"

/**
  @section Constants Definitions
*/
const time_t TIME_MAX = UINT32_MAX;

/**
  @section Global Variables Definitions
*/
static volatile time_t system_ticks = 0;

/**
  @section Systick APIs
*/

void ISR_Systick_Callback(void)
{
    //Number of Ticks since module was started
    ++system_ticks;
}

void Systick_Init ( void )
{
}

time_t Time_Now ( void )
{
    return system_ticks ;
}

time_t Time_Passed (time_t since)
{
    time_t now = system_ticks;

    if ( now >= since )
    {
        return (now - since );
    }

    // rollover has occured
    return ( now + ( TIME_MAX - since ));
}

/**
  End of File
*/
