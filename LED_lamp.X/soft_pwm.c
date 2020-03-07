
#include "soft_pwm.h"
#include "mcc_generated_files/tmr0.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/delay.h"

#define PWM_RESOLUTION 255

static uint8_t frequency;
static volatile uint8_t dutycycle [PWM_CHANNEL_MAX] = {0};

void ISR_PWM (void)
{

    static volatile uint16_t int_counter = 0;
    
    ++int_counter;
    
    for (uint8_t i = 0; i < PWM_CHANNEL_MAX; i++)
    {
        if ( int_counter <= dutycycle[i]  )
        {
            //Set IO High
            //GPIO_Set ()
            IO_RA4_SetHigh();
        }
        else
        {
            //Set IO Low
            IO_RA4_SetLow();
        }
    }
    
    if ( int_counter >= PWM_RESOLUTION)
    {
        int_counter = 0;
    }

}

void Soft_PWM_Init ( void )
{
   TMR0_SetInterruptHandler(ISR_PWM);
}


void Soft_PWM_Set_Duty ( pwm_channel_t channel, uint8_t duty )
{
    if ( channel >= PWM_CHANNEL_MAX)
    {
        return;
    }
    
    for (uint8_t i = 0; i < PWM_CHANNEL_MAX; i++)
    {
        if ( channel == i)
        {
            dutycycle[i] = duty;
        }
    }
 
}