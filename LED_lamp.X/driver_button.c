
#include "driver_button.h"
#include "mcc_generated_files/tmr2.h"
#include "mcc_generated_files/pin_manager.h"

#define DEBOUNCE_TIME		0.3
#define SAMPLE_FREQUENCY	10
#define MAXIMUM             (uint8_t)(DEBOUNCE_TIME * SAMPLE_FREQUENCY)

static button_event_t flag_press, flag_release, flag_held;
static volatile button_state_t button_state;

void ISR_Button_Debounce (void)
{
/* 0 or 1 depending on the input signal */
volatile int8_t input;       
/* Will range from 0 to the specified MAXIMUM */
volatile static uint8_t integrator = 0;
/* Cleaned-up version of the input signal */
volatile uint8_t output;      

/* Step 1: Update the integrator based on the input signal.  Note that the 
integrator follows the input, decreasing or increasing towards the limits as 
determined by the input state (0 or 1). */
    input = IO_RA2_GetValue();

    if (input == 0)
    {
        if (integrator > 0)
        {
            integrator--;
        }
    }
    else if (integrator < MAXIMUM)
    {
        integrator++;
    }

/* Step 2: Update the output state based on the integrator.  Note that the
output will only change states if the integrator has reached a limit, either
0 or MAXIMUM. */
    if (integrator == 0)
    {
        output = 0;
    }
    else if (integrator >= MAXIMUM)
    {
        output = 1;

        /* defensive code if integrator got corrupted */
        integrator = MAXIMUM;  
    }

    if( output == 1)
    {
        button_state = 1;
    }
    else
    {
        button_state = 0;
    }

}


void Button_Driver_Init (void )
{
    TMR2_SetInterruptHandler( ISR_Button_Debounce );
}
    
button_state_t Button_Read_State ( button_channel_t channel )
{
    return button_state;
}

button_event_t Button_Scan  ( button_channel_t channel )
{
    static button_state_t current_button_state = BUTTON_STATE_HIGH, previous_button_state;

    if ( channel >= BUTTON_CHANNEL_MAX )
    {
        return 0xff;
    }
    
    
    previous_button_state = current_button_state;
    current_button_state = Button_Read_State( channel );
    
    if ( current_button_state == BUTTON_STATE_LOW && previous_button_state ==  BUTTON_STATE_HIGH )
    {
        flag_press = BUTTON_EVENT_PRESSED;
    }
    
    if ( current_button_state == BUTTON_STATE_HIGH && previous_button_state ==  BUTTON_STATE_HIGH )
    {
        flag_held = BUTTON_EVENT_HELD;
    }
    
    if ( current_button_state == BUTTON_STATE_HIGH && previous_button_state ==  BUTTON_STATE_LOW )
    {
        flag_release = BUTTON_EVENT_RELEASED;
    }       
    
    return 0;
}

void Button_Clear_Events ( void )
{      
    flag_press      = BUTTON_EVENT_NONE;
    flag_held       = BUTTON_EVENT_NONE;
    flag_release    = BUTTON_EVENT_NONE; 
}
    
button_event_t Button_Get_Pressed_Event ( void )
{
    return flag_press;
}
button_event_t Button_Get_Held_Event ( void )
{
    return flag_held;
}
button_event_t Button_Get_Released_Event ( void )
{
    return flag_release;
}