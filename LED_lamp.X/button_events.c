#include "button_events.h"
#include "driver_button.h"
#include "systick.h"

double_click_state_t Double_Click_Run ( void )
{
    time_t const double_click_timeout = 300;
    static time_t  double_click_timeout_start;
    static double_click_state_t state = STATE_IDLE;
    
    switch ( state )
    {
        case STATE_IDLE:
            if ( Button_Get_Pressed_Event() ==  BUTTON_EVENT_PRESSED)
            {
                double_click_timeout_start = Time_Now();
                state = STATE_WAIT;
            }            
            break;
        
        case STATE_WAIT:
            if ( Button_Get_Pressed_Event() ==  BUTTON_EVENT_PRESSED)
            {
                state = STATE_SUCCESS;
            }             
                
            if ( Time_Passed(double_click_timeout_start) > double_click_timeout) 
            {
                state =  STATE_IDLE;             
            }          

            break;
        case STATE_SUCCESS:
            if ( Button_Get_Released_Event() ==  BUTTON_EVENT_RELEASED)
            {
                state = STATE_IDLE;
            }
            break;
    }
	return state;
}


double_click_state_t Hold_Button_Run ( void )
{
    time_t const double_click_timeout = 1000;
    static time_t  double_click_timeout_start;
    static double_click_state_t state = STATE_IDLE;
    
    switch ( state )
    {
        case STATE_IDLE:
            if ( Button_Get_Pressed_Event() ==  BUTTON_EVENT_PRESSED)
            {
                double_click_timeout_start = Time_Now();
                state = STATE_WAIT;
            }            
            break;
        
        case STATE_WAIT:
            if ( Button_Get_Released_Event() ==  BUTTON_EVENT_RELEASED)
            {
                state = STATE_IDLE;
            }             
            
            if ( Time_Passed(double_click_timeout_start) > double_click_timeout) 
            {
                state =  STATE_SUCCESS;             
            }
            break;
        case STATE_SUCCESS:
            if ( Button_Get_Released_Event() ==  BUTTON_EVENT_RELEASED)
            {
                state = STATE_IDLE;
            } 
            break;
    }
	return state;
}