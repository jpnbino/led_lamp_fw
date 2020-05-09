/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC12F1840
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "soft_pwm.h"
#include "driver_button.h"
#include "book_lamp_app.h"
#include "systick.h"
#include "light.h"

void Blink_Light ( void );
void Toggle_Light_When_Hold ( void );

//PWM Wrappers
void PWM_White_Set (uint8_t duty_cycle )
{   
    Soft_PWM_Set_Duty(PWM_CHANNEL1, duty_cycle); 
}

void PWM_Yellow_Set (uint8_t duty_cycle )
{
    Soft_PWM_Set_Duty(PWM_CHANNEL2, duty_cycle);
}

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    
    
    IO_RA5_SetHigh();
    DELAY_milliseconds(200);
    IO_RA5_SetLow();
    
    Button_Driver_Init();
    Soft_PWM_Init();
    Systick_Init();
    
    light_init_t light_init;
    light_init.white_color_pwm_set = &PWM_White_Set;
    light_init.yellow_color_pwm_set = &PWM_Yellow_Set;
    Light_Init(light_init);

    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    Book_Lamp_Init();
    
    Button_Scan(0);
    DELAY_milliseconds(20);
    Button_Scan(0);
    Button_Clear_Events();
    
    while (1)
    {
        CLRWDT();
        
        Book_Lamp_App();
        //Toggle_Light_When_Hold();
        //Blink_Light();
    }
}

void Blink_Light ( void )
{
   time_t const LED_TOGGLE_TIMEOUT = 3000; 
   static time_t led_toggle_time_start = 0; 
   
   if ( Time_Now() - led_toggle_time_start > LED_TOGGLE_TIMEOUT)
   {
       led_toggle_time_start = Time_Now(); 
       IO_RA4_Toggle();
   }
   
}

void Toggle_Light_When_Hold ( void )
{
    time_t const LED_TOGGLE_TIMEOUT = 500; 
    static time_t led_toggle_time_start = 0; 
    static uint8_t flag_counter_on = 0; 
   
    Button_Scan(0);
    if ( Button_Get_Pressed_Event() == BUTTON_EVENT_PRESSED )
    {
        led_toggle_time_start = Time_Now(); 
        flag_counter_on = 1;
    }

    if ( flag_counter_on == 1)
    {
        if ( Time_Now() - led_toggle_time_start > LED_TOGGLE_TIMEOUT)
        {
            led_toggle_time_start = Time_Now(); 
            IO_RA4_Toggle();
        }
    }
    
    if ( Button_Get_Released_Event() == BUTTON_EVENT_RELEASED)
    {
        flag_counter_on = 0;
    }
    
    Button_Clear_Events();    
}

/**
 End of File
*/