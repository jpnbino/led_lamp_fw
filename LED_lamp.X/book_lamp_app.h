/**
 @brief Application API to control a book lamp light.
  
 @file book_lamp_app.h
 @author Joao P bino
 */

#ifndef BOOK_LAMP_APP_H
#define	BOOK_LAMP_APP_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

    /**
     @brief Init application
     
     @param None
    
     @return None
    */
    void Book_Lamp_Init ( void );
    
    /**
     @brief Run the application
     
     @param None
    
     @return None
    */
    void Book_Lamp_App ( void );

#ifdef	__cplusplus
}
#endif

#endif	/* BOOK_LAMP_APP_H */

