
#include "book_lamp_app.h"
#include "driver_button.h"
#include "soft_pwm.h"
#include "mcc_generated_files/delay.h"

typedef enum {
    
    STATE_OFF,
    STATE_WARM_LIGHT,
    STATE_MILD_LIGHT,
    STATE_WHITE_LIGHT,
    STATE_CHANGE_LIGHT_INTENSITY,
}state_t;

typedef enum {
    EVENT_NONE,
    EVENT_TIMEOUT,
    EVENT_BUTTON_RELEASED,
    EVENT_DOUBLE_CLICK,
}event_t;

void Timeout_Handler (void)
{
    //Changes light intensity    
}

event_t Get_Event ( void )
{
    event_t event ;

    Button_Scan( 0 );
    
    if ( Button_Get_Released_Event())
    {
        event = EVENT_BUTTON_RELEASED;
    }
    else
    {
        event = EVENT_DOUBLE_CLICK;
    }
        
    
    Button_Clear_Events();
    return event;
}

void Book_Lamp_App ( void )
{
    static state_t state = STATE_OFF;
    event_t event = EVENT_NONE;
    
    event = Get_Event();

    if ( state != STATE_OFF )
    {
        if ( event == EVENT_TIMEOUT )
        {
            Timeout_Handler();
        }
    }
    
    switch ( state )
    {
        case  STATE_OFF:
            if ( event == EVENT_BUTTON_RELEASED )
            {
                Soft_PWM_Set_Duty (PWM_CHANNEL1, 0);
                Soft_PWM_Set_Duty (PWM_CHANNEL2, 200 );
                state = STATE_WARM_LIGHT;
            }             
            break;
            
        case STATE_WARM_LIGHT:  
            if ( event == EVENT_BUTTON_RELEASED )
            {
                Soft_PWM_Set_Duty (PWM_CHANNEL1, 200);
                Soft_PWM_Set_Duty (PWM_CHANNEL2, 200 );
                state = STATE_MILD_LIGHT;                  
            }
            break;
            
        case STATE_MILD_LIGHT:
            if ( event == EVENT_BUTTON_RELEASED )
            {
                Soft_PWM_Set_Duty (PWM_CHANNEL1, 200  );
                Soft_PWM_Set_Duty (PWM_CHANNEL2, 0 );
                state = STATE_WHITE_LIGHT;               
            }
            break;
            
        case STATE_WHITE_LIGHT:
            if ( event == EVENT_BUTTON_RELEASED )
            {
                Soft_PWM_Set_Duty (PWM_CHANNEL1, 0);
                Soft_PWM_Set_Duty (PWM_CHANNEL2, 0 );
                state = STATE_OFF;
            }            
            break;

        default:
            break;    
    }
    
}