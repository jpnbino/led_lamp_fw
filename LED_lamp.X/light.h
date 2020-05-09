/*
 * File:   driver_button.h
 * Author: jpnbino
 *
 * Created on March 22, 2020, 10:04 PM
 */

#ifndef LIGHT_H
#define	LIGHT_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct 
    {
        void (*white_color_pwm_set) (uint8_t);
        void (*yellow_color_pwm_set) (uint8_t);
        uint8_t pwm_resolution;

    }light_init_t;

    typedef struct
    {
        uint8_t white;
        uint8_t yellow;
    }light_t;

    void Light_Init(light_init_t light_init);
    void Set_Light_Brightness(light_t light);



#ifdef	__cplusplus
}
#endif

#endif	/* LIGHT_H */

