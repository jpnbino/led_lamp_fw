/*
 * File:   systick.h
 * Author: jpnbino
 *
 * Created on 17 de Abril de 2020, 20:38
 */

#ifndef SYSTICK_H
#define	SYSTICK_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

    typedef uint32_t time_t;
    /******************************************************************************
     Function Name: Systick_Init
    *******************************************************************************
     Summary:
    	Initializes systick.

     Parameters:
    	None

     Return:
        None

     Note:
     	None
    ******************************************************************************/
    void Systick_Init   ( void );
    /******************************************************************************
    * Function Name: Time_Now
    *******************************************************************************
     Summary:
    	Gives the number of Ticks since the module was initialized

     Parameters:
    	None

     Return:
      	Number of Ticks since system was booted

     Example:
       uint32_t time_now;
       Systick_Count_Update();
       time_now = Time_Now();

     Note:
     	None
    ******************************************************************************/
    time_t Time_Now ( void );

    /******************************************************************************
    * Function Name: Time_Passed
    *******************************************************************************
     Summary:
    	Calculates the time passed since a specific tick.


     Parameters:
    	since - Value in Ticks of a given time.

     Return:
      	time_passed - time in ticks passed since a given time.

     Example:
       const time_t WAIT_TIMEOUT = 300;
       time_t last_execution
       last_execution = Time_Now();

    	if ( Time_Passed ( last_execution )) > WAIT_TIMEOUT)
       {
           Do_Something();
       }

     Note:
     	None
    ******************************************************************************/
    time_t Time_Passed (time_t since);


#ifdef	__cplusplus
}
#endif

#endif	/* SYSTICK_H */

