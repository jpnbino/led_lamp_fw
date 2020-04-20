/* 
 * File:   driver_button.h
 * Author: jpnbino
 *
 * Created on March 22, 2020, 10:04 PM
 */

#ifndef DRIVER_BUTTON_H
#define	DRIVER_BUTTON_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum {
        BUTTON_CHANNEL_1,
        BUTTON_CHANNEL_MAX,
    }button_channel_t;
    
    typedef enum {
        BUTTON_STATE_LOW,
        BUTTON_STATE_HIGH,
    }button_state_t;
    
    typedef enum {
        BUTTON_EVENT_NONE,
        BUTTON_EVENT_PRESSED,
        BUTTON_EVENT_RELEASED,
        BUTTON_EVENT_HELD,         
    }button_event_t;
    
    void Button_Driver_Init (void );
    void Button_Clear_Events ( void );
    button_state_t Button_Read_State ( button_channel_t channel );
    button_event_t Button_Scan  ( button_channel_t channel );
    button_event_t Button_Get_Pressed_Event ( void );
    button_event_t Button_Get_Released_Event ( void );
    button_event_t Button_Get_Held_Event ( void );
    
#ifdef	__cplusplus
}
#endif

#endif	/* DRIVER_BUTTON_H */

