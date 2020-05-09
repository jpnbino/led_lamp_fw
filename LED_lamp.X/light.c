
#include "light.h"
//Color and Brightness


void (*white_color_pwm_set) (uint8_t);
void (*yellow_color_pwm_set) (uint8_t);


void Light_Init ( light_init_t light_init)
{
    white_color_pwm_set = light_init.white_color_pwm_set;
    yellow_color_pwm_set = light_init.yellow_color_pwm_set;
}

void Set_Light_Brightness ( light_t light)
{
    white_color_pwm_set(light.white);
    yellow_color_pwm_set(light.yellow);
}