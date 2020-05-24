/*
 * File:   soft_pwm.h
 * Author: jpnbino
 *
 * Created on 5 de Mar�o de 2020, 23:18
 */

#ifndef SOFT_PWM_H
#define	SOFT_PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>


    typedef enum {
        PWM_CHANNEL1,
        PWM_CHANNEL2,
        PWM_CHANNEL_MAX,
    }
    pwm_channel_t;
    void ISR_PWM_Callback ( void );
    void Soft_PWM_Init ( void );
    void Soft_PWM_Set_Duty ( pwm_channel_t channel, uint8_t duty );



#ifdef	__cplusplus
}
#endif

#endif	/* SOFT_PWM_H */

