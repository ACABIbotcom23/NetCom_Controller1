#ifndef TEST_DATA_HPP
#define TEST_DATA_HPP

#include <stdlib.h>

struct send_data_1{
    uint8_t Battery_Level;
    uint8_t Status_Code[2];
    float GPS_Data[3];

};

struct send_data_2{
    int16_t Sensor_Data[300][5];

};

uint8_t BATTERY_LEVEL_TEST1 = 100;
uint8_t STATUS_CODE_TEST1[2] = {99, 98};
float GPS_DATA_TEST1[3] = {33.8, 35.7, 9.21};
int16_t SENSOR_DATA_TEST1[300][5] = {55};

uint8_t BATTERY_LEVEL_TEST2 = 98;
uint8_t STATUS_CODE_TEST2[2] = {97, 96};
float GPS_DATA_TEST2[3] = {9.8, 30.7, 10.21};
int16_t SENSOR_DATA_TEST2[300][5] = {52};

send_data_1 TEST_DATA_1;
send_data_2 TEST_DATA_2;


#endif