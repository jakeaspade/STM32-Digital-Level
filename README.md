# STM32-Digital-Level
This repository is a Digital Leveler using a stm32f4, a 8-bit shift register, some leds, and a MPU6050 module

## High Level Overview
The leveler uses the MPU6050's accelerometer to determine the tilt of the system.  The readings from the x and y axies are read from the module using the I2C protocol.  After getting the values, a byte of data is created representing the the LEDs in the system which will help visualize if the system is level.  That byte is transmitted using the SPI protocol to the 74HC595 Shift Register to control all LEDs while minimizing pins used on the board.
