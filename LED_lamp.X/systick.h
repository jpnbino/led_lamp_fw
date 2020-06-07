/**
 @brief File containing Definitions and API Systick implementations.

This source file provides APIs time counting for timed events.
  
 @file systick.h
 @author Joao P bino
 */

#ifndef SYSTICK_H
#define	SYSTICK_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

    typedef uint32_t time_t;
    
    /**
     @brief Updates the tick count. 
     The size of tick depends upon the timer period attached to it. If timer has
     a period of 1ms then the tick is 1ms.
    
     @param None
    
     @return None
    
     @note This function needs to be called from within an ISR.
    */
    void ISR_Systick_Callback(void);
    
    /**
     @brief Initializes systick.

     @param	None

     @return None

     @note None
    */
    void Systick_Init (void);
    
    /**
     @brief Gives the number of Ticks since the module was initialized

     @param None

     @return Number of Ticks since system was booted

     Example:
    @code
        //Generic ISR calling
        timer_ISR(void)
        {
            ISR_Systick_Callback();
        }
        uint32_t time_now;
        Systick_Count_Update();
        time_now = Time_Now();
     @endcode

     @note
     	None
    */
    time_t Time_Now (void);

    /**
     @brief
    	Calculates the time passed since a specific tick.


     @param
    	since - Value in Ticks of a given time.

     @return
      	time_passed - time in ticks passed since a given time.

     Example:
        @code
        main()
        {
            const time_t WAIT_TIMEOUT = 300;
            time_t last_execution
            last_execution = Time_Now();

            if ( Time_Passed ( last_execution )) > WAIT_TIMEOUT)
            {
               Do_Something();
            }
        }
        @endcode
     @note
     	None
    */
    time_t Time_Passed (time_t since);


#ifdef	__cplusplus
}
#endif

#endif	/* SYSTICK_H */

/**
  End of File
*/