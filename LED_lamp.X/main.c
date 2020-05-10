#include "mcc_generated_files/mcc.h"
#include "soft_pwm.h"
#include "driver_button.h"
#include "book_lamp_app.h"
#include "systick.h"
#include "light.h"

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

    Button_Scan(BUTTON_CHANNEL_0);
    DELAY_milliseconds(20);
    Button_Scan(BUTTON_CHANNEL_0);
    Button_Clear_Events();

    while (1)
    {
        CLRWDT();
        Book_Lamp_App();
    }
}

/**
 End of File
*/