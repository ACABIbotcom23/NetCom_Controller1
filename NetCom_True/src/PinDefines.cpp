#include "PinDefines.hpp"

TwoWire C1_C2 = TwoWire(0);
TwoWire Bat_C1 = TwoWire(1);

void set_i2c_C2_C1(){
    C1_C2.begin(I2C_SDA_C2_C1, I2C_SCL_C2_C1);
}

void set_i2c_Bat_C1(){
    Bat_C1.begin(I2C_SDA_Bat_C1, I2C_SCL_Bat_C1);
}

void set_uart_Sat_C1(){
    //should already be using GPIO 1 & 3 by default
    Serial1.begin(9600, SERIAL_8N1, UART_RX0_Sat_C1, UART_TX0_Sat_C1);
}

void set_uart_GNSS_C1(){
    Serial2.begin(9600, SERIAL_8N1, UART_RX1_GNSS_C1, UART_TX1_GNSS_C1);
}

void init_pins(){
    set_i2c_C2_C1();
    set_i2c_Bat_C1();
    set_uart_Sat_C1();
    set_uart_GNSS_C1();

}