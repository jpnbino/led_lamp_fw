/**
@brief main file.
@file main.c
@author Joao P Bino
*/

#include "mcc_generated_files/mcc.h"
#include "soft_pwm.h"
#include "driver_button.h"
#include "book_lamp_app.h"
#include "systick.h"
#include "light.h"

/**
 @brief Wrapper function comply with HAL function. 

 This function is a wrapper to comply the HAL function to control the PWM to 
 the function that controls the light intensity of the white light.
 
 @param [in]   PWM Duty Cycle for white color
 @return None

 @see Soft_PWM_Set_Duty
 @see Set_Light_Brightness
*/
void PWM_White_Light_Set (uint8_t duty_cycle )
{
    Soft_PWM_Set_Duty(PWM_CHANNEL1, duty_cycle);
}

/**
 @brief Wrapper function comply with HAL function. 

 This function is a wrapper to comply the HAL function to control the PWM to 
 the function that controls the light intensity of the yellow light.
 
 @param [in]   PWM Duty Cycle for yellow color
 @return None

 @see Soft_PWM_Set_Duty
 @see Set_Light_Brightness
*/
void PWM_Yellow_Light_Set (uint8_t duty_cycle )
{
    Soft_PWM_Set_Duty(PWM_CHANNEL2, duty_cycle);
}

/*
    Main application
 */
void main(void)
{    
    /* Initializes the Lower level drivers and system. Provided by manufacturer. */
    SYSTEM_Initialize();
 
    /* Set interrupt callback function */
    TMR0_SetInterruptHandler(ISR_PWM_Callback);
    TMR1_SetInterruptHandler(ISR_Systick_Callback);
    TMR2_SetInterruptHandler(ISR_Button_Debounce_Callback);
    
    /* Init application drivers */
    Button_Driver_Init();
    Soft_PWM_Init();
    Systick_Init();
    
    light_init_t light_init;
    light_init.white_color_pwm_set = &PWM_White_Light_Set;
    light_init.yellow_color_pwm_set = &PWM_Yellow_Light_Set;
    Light_Init(light_init);
 
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();

    Book_Lamp_Init();

    while (1)
    {
        /* Clear Watchdog */
        CLRWDT();
        
        /* run application */
        Book_Lamp_App();
    }
}

/**
 End of File
*/