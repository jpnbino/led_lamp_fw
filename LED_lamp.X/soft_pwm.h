/**
 @brief File containing Definitions and API of software pwm.

 This API allows the control of a software pwm which needs a timer interrupt to 
 work. There is a interrupt callback that must be called from whithin the timer
 interrupt service routine.
 
 @file soft_pwm.h
 @author Joao P bino
 */

#ifndef SOFT_PWM_H
#define	SOFT_PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

    /** Defines the period of the PWM. 
     if period is 100 and duty cycle is 30. Then, the output is
     High for 30 steps and low for 70 steps */
    #define PWM_RESOLUTION 100

    typedef enum {
        PWM_CHANNEL1,
        PWM_CHANNEL2,
        PWM_CHANNEL_MAX,
    }
    pwm_channel_t;
    
    /**
     @brief Switch the PWM output based on chosen duty cycle for the channel. 
     
     Controls the output for each PWM channel. At every call, this function
     checks if the duty cycle for each channel was reached.

     @param None   
     @return None
    
     @note This function needs to be called from within a timer ISR.
     @see Soft_PWM_Set_Duty
    */
    void ISR_PWM_Callback ( void );
    
    /**
     @brief Initializes software PWM module.

     @return None

     @note None
    */
    void Soft_PWM_Init (void);

    /**
     @brief Gives the number of Ticks since the module was initialized

     @param [in] channel: PWM output channel
     @param [in] duty: Duty cycle of the PWM
     @return Number of Ticks since system was booted

     Example:
     @code
        void Soft_PWM_Init ( );
        Soft_PWM_Set_Duty(PWM_CHANNEL1, 50);

     @endcode

     @note duty parameter is limited by PWM_RESOLUTION macro.
     @see PWM_RESOLUTION
    */
    void Soft_PWM_Set_Duty ( pwm_channel_t channel, uint8_t duty );



#ifdef	__cplusplus
}
#endif

#endif	/* SOFT_PWM_H */

