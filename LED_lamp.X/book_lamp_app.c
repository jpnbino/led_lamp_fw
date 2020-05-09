
#include "book_lamp_app.h"
#include "driver_button.h"
#include "soft_pwm.h"
#include "systick.h"
#include "button_events.h"
#include "light.h"

#define ARRAYSIZE(arr) (sizeof(arr) / sizeof(arr[0]))

static uint8_t brightness;
uint8_t const set_brightness[5] = {30,80,120,200,255};

static light_t light_brightness;
static light_t light_ratio;
// In percentage
light_t const light_temperature_ratio[5] = 
{
    { 0,100 },
    { 25,75 },
    { 50,50 },
    { 75,25 },
    { 100,0 },
};

typedef enum { 
    STATE_OFF,
    STATE_CHANGE_LIGHT_TEMPERATURE,
    STATE_CHANGE_LIGHT_BRIGTHNESS,
}state_t;

typedef enum {
    EVENT_NONE,
    EVENT_BUTTON_RELEASED,
    EVENT_DOUBLE_CLICK,
    EVENT_CHANGE_BRIGHTNESS
}event_t;

void Book_Lamp_Set_Light( light_t light)
{
    static uint8_t white;
    static uint8_t yellow;
    
    light_brightness.white = (brightness * light_ratio.white)/ ( light_ratio.white + light_ratio.yellow);
            
    light_brightness.yellow = (brightness * light_ratio.yellow)/ ( light_ratio.white + light_ratio.yellow);
    
    Set_Light_Brightness(light_brightness);   
}

void Event_Turn_On_Handler ( void )
{
    light_t light = {brightness,brightness};
    Book_Lamp_Set_Light(light);
}

void Event_Turn_Off_Handler( void )
{
    light_t light = { 0,0 };
    Set_Light_Brightness(light);
}


void Event_Change_Brightness_Handler( void )
{
    static uint8_t i = 0;
    static uint8_t white;
    static uint8_t yellow;
    
    if ( i >= ARRAYSIZE ( set_brightness))
    {
        i = 0;
    }
    brightness = set_brightness[i++];
    
    Book_Lamp_Set_Light ( light_brightness);
}


void Event_Change_Temperature_Handler( void )
{
    static uint8_t i = 1;
    
    if ( i >= ARRAYSIZE ( light_temperature_ratio))
    {
        i = 0;
    }
  
    light_ratio = light_temperature_ratio[i++];
    
    Book_Lamp_Set_Light ( light_ratio);

}

event_t Get_Event ( void )
{
    event_t event = EVENT_NONE;
    static uint8_t wait_more_than_double_click_timeout;
    static uint8_t button_release_request = 0;
    double_click_state_t double_click_state = STATE_IDLE;
    double_click_state_t sdouble_click_state = STATE_IDLE;
    
    static uint8_t start_repeat = 0;
    static time_t hold_time_start;
    time_t const hold_timeout = 800;
          
    Button_Scan( 0 );

    sdouble_click_state = double_click_state;
    double_click_state = Double_Click_Run();

    if ( double_click_state == STATE_SUCCESS)
    {
        event = EVENT_DOUBLE_CLICK; 
    }
    
    if ( Hold_Button_Run() == STATE_SUCCESS )
    {       
        if ( start_repeat )
        {
            if (Time_Passed(hold_time_start) > hold_timeout)
            {
                event = EVENT_CHANGE_BRIGHTNESS;
                hold_time_start = Time_Now(); 
            }
        }
        else
        {
           start_repeat = 1;
           hold_time_start = Time_Now(); 
        }
    }
    
    if ( Button_Get_Released_Event() )
    {
        start_repeat = 0;
    }
    
    //Change Temperature Event
    if ( Button_Get_Released_Event() ==  BUTTON_EVENT_RELEASED)
    {
        event = EVENT_BUTTON_RELEASED; 
    }

    Button_Clear_Events();
    return event;
}

void Book_Lamp_Init ( void )
{
    brightness = set_brightness[0];
    light_ratio = light_temperature_ratio[0];
    Event_Turn_Off_Handler();
}

void Book_Lamp_App ( void )
{
    static state_t state = STATE_OFF;
    event_t event = EVENT_NONE;
    
    event = Get_Event();
    
    switch ( state )
    {
        case  STATE_OFF:
            if ( event == EVENT_BUTTON_RELEASED )
            {
                Event_Turn_On_Handler();
                state = STATE_CHANGE_LIGHT_TEMPERATURE;
            }             
            break;
            
        case STATE_CHANGE_LIGHT_TEMPERATURE:  
            if ( event == EVENT_BUTTON_RELEASED )
            {
                Event_Change_Temperature_Handler();
                state = STATE_CHANGE_LIGHT_TEMPERATURE;                  
            }
            if (event == EVENT_DOUBLE_CLICK)
            {
                Event_Turn_Off_Handler();
                state = STATE_OFF;
            }
            break;
            
        case STATE_CHANGE_LIGHT_BRIGTHNESS:
            if ( event == EVENT_BUTTON_RELEASED )
            {
                state = STATE_CHANGE_LIGHT_TEMPERATURE;               
            }
            
            if ( event == EVENT_CHANGE_BRIGHTNESS )
            {
                Event_Change_Brightness_Handler();
            }
            break;

        default:
            break;    
    }
    
}