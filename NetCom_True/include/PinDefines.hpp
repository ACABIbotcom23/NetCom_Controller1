#ifndef PINDEFINES_HPP
#define PINDEFINES_HPP

/*
This file contains all the pins used for Controller 1 of the Firmware.

This file will also set pins to specific functions such as setting pins
for UART and I2C more at the bottom.
*/

/*
Useable Pins:

Number/Name |   Function    |
            |               |                 
- GPIO 25   |   UART TX0    |                                    
- GPIO 26   |   UART RX0    |                                         
- GPIO 16   |   UART RX1    |
- GPIO 17   |   UART TX1    |
- GPIO 21   |   SDA         | 
- GPIO 22   |   SCL         |
*/

#include "driver/i2c.h"
#include "driver/uart.h"
#include "Wire.h"
#include "HardwareSerial.h"

#define UART_TX0_Sat_C1     25
#define UART_RX0_Sat_C1     26

#define UART_TX1_GNSS_C1    17
#define UART_RX1_GNSS_C1    16

#define I2C_SCL_C2_C1       22
#define I2C_SDA_C2_C1       21

#define I2C_SCL_Bat_C1      32
#define I2C_SDA_Bat_C1      33

extern TwoWire C1_C2;
extern TwoWire Bat_C1;

void set_i2c_C2_C1();
void set_i2c_Bat_C1();
void set_uart_Sat_C1();
void set_uart_GNSS_C1();

void init_pins();


#endif