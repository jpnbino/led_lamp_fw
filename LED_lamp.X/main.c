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
    

    static uint16_t i = 0;
    pwm_channel_t pwm_channel = PWM_CHANNEL1;
    
    
    while (1)
    {
        CLRWDT();
        Button_Scan( 0 );
        
        if ( Button_Get_Pressed_Event() == BUTTON_EVENT_PRESSED)
        {
            Soft_PWM_Set_Duty(pwm_channel, 100);
        }

        if ( Button_Get_Released_Event() == BUTTON_EVENT_RELEASED)
        {
            Soft_PWM_Set_Duty(pwm_channel, 0);
        }
        
        Button_Clear_Events();
        
#if 0 
        if ( i <= 255)
        {
            i++;
            Soft_PWM_Set_Duty(pwm_channel, i);
            DELAY_milliseconds(10);
        }
        else
        {
            i = 0;
            DELAY_milliseconds(100);
            Soft_PWM_Set_Duty(pwm_channel, i);
            DELAY_milliseconds(100);
            
            pwm_channel++;
            
            if (pwm_channel >= PWM_CHANNEL_MAX  )
            {
                pwm_channel = PWM_CHANNEL1;
            }
        }
#endif
    }
}
/**
 End of File
*/