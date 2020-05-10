
#include "soft_pwm.h"
#include "mcc_generated_files/tmr0.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/delay.h"

#define PWM_RESOLUTION 255

static uint8_t frequency;
static volatile uint16_t dutycycle [PWM_CHANNEL_MAX] = {0};
static volatile uint8_t pwm_channel[PWM_CHANNEL_MAX] = {0};
static volatile uint8_t gpio_channel[PWM_CHANNEL_MAX] =
{
    _LATA_LATA4_POSITION,
    _LATA_LATA5_POSITION,

};


void GPIO_Channel_Write ( uint8_t channel, uint8_t state )
{
    if ( state )
    {
        LATA = LATA | (1 << channel);
    }
    else
    {
        LATA = LATA & (0xff & (0 << channel));
    }

}

void ISR_PWM (void)
{
    static volatile uint16_t interrupt_counter = 0;

    for (uint8_t i = 0; i < 2; i++)
    {
        if ( interrupt_counter < dutycycle[i]  )
        {
            GPIO_Channel_Write(pwm_channel[i],1 );
        }
        else
        {
            GPIO_Channel_Write(pwm_channel[i],0 );
        }
    }

    ++interrupt_counter;

    if ( interrupt_counter >= PWM_RESOLUTION)
    {
        interrupt_counter = 0;
    }

}

void Soft_PWM_Init ( void )
{

    TMR0_SetInterruptHandler(ISR_PWM);

    for (uint8_t i = 0; i < PWM_CHANNEL_MAX; i++)
    {
        pwm_channel[i] = gpio_channel[i];
    }

    Soft_PWM_Set_Duty(PWM_CHANNEL1, 0);
    Soft_PWM_Set_Duty(PWM_CHANNEL2, 0);

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