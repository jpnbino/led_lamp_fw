

#ifndef BUTTON_EVENTS_H
#define	BUTTON_EVENTS_H

#ifdef	__cplusplus
extern "C" {
#endif

    /**@TODO: Put here the time config for the events like double click time */

    typedef enum {
        ST_CLICK_IDLE,                              /*!< IDLE STATE */
        ST_CLICK_WAIT,                              /*!< WAIT STATE */
        ST_CLICK_WAIT_DOUBLE,                       /*!< WAIT DOUBLE CLICK STATE */
        ST_CLICK_SINGLE,                            /*!< SINGLE CLICK STATE */
        ST_CLICK_DOUBLE,                            /*!< DOUBLE CLICK STATE */
        ST_CLICK_LONG,                              /*!< LONG CLICK STATE */
    }
    click_state_t;

    /**
     @brief Reads events from buttons like double click. 
     
     @param None
    
     @return check click_state_t
    
     @note This function needs to be called from within an ISR.
    */
    click_state_t Get_Click_Event ( void );

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTON_EVENTS_H */

