/* 
 * File:   low_power.h
 * Author: jpnbino
 *
 * Created on February 15, 2021, 4:06 PM
 */

#ifndef LOW_POWER_H
#define	LOW_POWER_H

#ifdef	__cplusplus
extern "C"
{
#endif

typedef enum
{
    SLEEP_MODE,
}low_power_mode_t;
    
void Enter_Low_Power_Mode ( low_power_mode_t mode );

#ifdef	__cplusplus
}
#endif

#endif	/* LOW_POWER_H */

