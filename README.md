# LED LAMP
LED lamp is a small project that started with the idea of adding more functionalities for my book lamp. It happened that I bought a led lamp with only one light intensity for each led color ( there was warm and cold white ) and it actually was too strong for reading and  therefore I needed a lighter intensity. Then I came up with the idea of replacing the controller of the book lamp with a small microchip microcontroller which was pin to pin compatible.

I shared more [here](https://www.element14.com/community/people/jpnbino/blog/2021/10/30/engineering-for-daily-life-hacking-my-reading-lamp)

## The Hardware
The book lamp is a battery powered device with 
 - one tactile button for interface.
 - 2 sets of led: WARM light and WHITE light

## How was the book lamp before ?
Everytime the button was pressed the lamp changed its state between: System Turned OFF, WARM LIGHT, WHITE LIGHT, and both lights ON. there was no intensity control.

## What was then implemented ?
As the lights were two strong, the first thing I thought was to implement a light intensity control. For that, I also extended the functionalities of the button to respond to events like :

- Single click ( to change the  light composition )
- Holding the button ( to change the brightness )
- and, Double click ( to turn off the device )

with those new events responses it was also implemented a new scheme of possible lights composition:

|SET | WARM (%) | WHITE(%)|
--- | --- | ---
|1 | 100 | 0|
|2 | 75 | 25|
|3 | 50 | 50|
|4 | 25 | 75|
|5 | 0  | 100|

Then, it was implemented a brightness control of 5 levels pre-defined.

```c
uint8_t const set_brightness[5] = {10,20,30,50,100};
```
100 represents 100% of brightness, 20 represents 20% and so on;

The percentage of each light is calculated by the formula below ( yellow refers to the warm light )

```c
light_brightness.white = (brightness * light_ratio.white)/ ( light_ratio.white + light_ratio.yellow);

light_brightness.yellow = (brightness * light_ratio.yellow)/ ( light_ratio.white + light_ratio.yellow);
```

## Environment info
- MCU: PIC12F1840
- Compiler: xc8 (v2.1)
