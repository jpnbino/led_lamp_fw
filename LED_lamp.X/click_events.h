/*
 * File:   button_events.h
 * Author: jpnbino
 *
 * Created on 31 de Mar�o de 2020, 23:01
 */

#ifndef BUTTON_EVENTS_H
#define	BUTTON_EVENTS_H

#ifdef	__cplusplus
extern "C" {
#endif



    typedef enum {
        ST_CLICK_IDLE,
        ST_CLICK_WAIT,
        ST_CLICK_WAIT_DOUBLE,
        ST_CLICK_SINGLE,
        ST_CLICK_DOUBLE,
        ST_CLICK_LONG,
    }
    click_state_t;

    click_state_t Get_Click_Event ( void );

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTON_EVENTS_H */

