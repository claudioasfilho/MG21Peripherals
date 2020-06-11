# MG21Peripherals

Latest Status:

PWM function works.



This demonstrate how to use Hardware peripherals with the MG21

Tools and SDKs:

This was tested with:

Silicon Labs Bluetooth Stack 2.13.5.0

GNU ARM 7.2.1

Development Board: Silicon Labs WSTK with BRD4180 (EFR32MG21A020F1024IM32)

Usage:

Please clone this to where your Simplicity Studio Workspace is located.

Then to import it, please do:

File -> Import -> More Import Options -> General -> Existing Projects Into Workspace -> Select Workspace directory -> Select Project -> Finish

The IADC portion of this code was based on the following Silabs GitHub Example:

https://github.com/SiliconLabs/peripheral_examples/tree/master/series2/iadc/iadc_single_em2

Hardware Connections:

PWM Pin - PC3 - WSTK EXP10 Header
ADC Pin - PC2 - WSTK EXP8 Header
Button0 - WSTK PB0
LED0 - WSTK LED0
