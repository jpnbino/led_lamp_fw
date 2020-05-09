
	
/******************************************************************************
* Includes
******************************************************************************/
#include "systick.h"
#include "mcc_generated_files/tmr1.h"
/******************************************************************************
* Constants
******************************************************************************/
const time_t TIME_MAX = UINT32_MAX;
/******************************************************************************
* Variables
******************************************************************************/
static volatile time_t system_ticks = 0; 

/******************************************************************************
* Function Implementation
******************************************************************************/

/******************************************************************************
* Function Name: ISR_Systick_Callback
*******************************************************************************
*
* Summary:
*  This API is called from SysTick timer interrupt handler to update the
*  millisecond counter.
*
* Parameters:
*  None
*
* Return:
*  None
*
******************************************************************************/
void ISR_Systick_Callback(void)
{
    //Number of Ticks since module was started 
    ++system_ticks;
}

void Systick_Init ( void )
{
    TMR1_SetInterruptHandler( ISR_Systick_Callback);
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
