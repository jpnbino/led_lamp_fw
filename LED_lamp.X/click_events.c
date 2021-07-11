#include "click_events.h"
#include "driver_button.h"
#include "systick.h"

click_state_t Get_Click_Event ( void )
{
    /* Time within two consecutives clicks are considered a double click.*/
    time_t const DOUBLE_CLICK_TIMEOUT = 300;
    /* If a button is held pressed for more than this time, the event is called
     button long press.*/
    time_t const LONG_CLICK_TIMEOUT = 700;

    static time_t  double_click_timeout_start;
    static time_t  long_click_timeout_start;

    static click_state_t state = ST_CLICK_IDLE;

    Button_Scan( 0 );
    
    switch ( state )
    {
    case ST_CLICK_IDLE:
        
        if ( Button_Get_Pressed_Event() ==  BUTTON_EVENT_PRESSED)
        {
            double_click_timeout_start = Time_Now();
            long_click_timeout_start = Time_Now();

            state = ST_CLICK_WAIT;
        }
        break;
        
    case ST_CLICK_WAIT:
        
        if ( Button_Get_Released_Event() ==  BUTTON_EVENT_RELEASED)
        {
            state = ST_CLICK_WAIT_DOUBLE;
        }

        if ( Time_Passed(long_click_timeout_start) > LONG_CLICK_TIMEOUT)
        {
            state =  ST_CLICK_LONG;
        }
        break;
        
    case ST_CLICK_LONG:
        
        if ( Button_Get_Released_Event() ==  BUTTON_EVENT_RELEASED)
        {
            state = ST_CLICK_IDLE;
        }
        break;
        
    case ST_CLICK_WAIT_DOUBLE:

        if ( Button_Get_Pressed_Event() ==  BUTTON_EVENT_PRESSED)
        {
            state =  ST_CLICK_DOUBLE;
        }

        if ( Time_Passed(double_click_timeout_start) > DOUBLE_CLICK_TIMEOUT)
        {
            state =  ST_CLICK_SINGLE;
        }

        break;
        
    case ST_CLICK_SINGLE:
        
        state = ST_CLICK_IDLE;
        break;
        
    case ST_CLICK_DOUBLE:
        
        state = ST_CLICK_IDLE;
        break;
        
    default:
        break;

    }

    Button_Clear_Events();
    
    return state;
}