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

void Blink_Light ( void );
void Toggle_Light_When_Hold ( void );
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
    //Soft_PWM_Init();
    Systick_Init();
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();
    
    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
  
    uint8_t flag_held_button_event;
    while (1)
    {
        CLRWDT();
        
        //Book_Lamp_App();
        Button_Scan(0);
        Toggle_Light_When_Hold();
        //Blink_Light();
        Button_Clear_Events();
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
    
}

/**
 End of File
*/