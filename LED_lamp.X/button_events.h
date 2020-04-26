/* 
 * File:   button_events.h
 * Author: jpnbino
 *
 * Created on 31 de Março de 2020, 23:01
 */

#ifndef BUTTON_EVENTS_H
#define	BUTTON_EVENTS_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum {
    STATE_IDLE,
    STATE_WAIT,
    STATE_SUCCESS,          
}double_click_state_t;


double_click_state_t Double_Click_Run ( void );
double_click_state_t Hold_Button_Run ( void );

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTON_EVENTS_H */

