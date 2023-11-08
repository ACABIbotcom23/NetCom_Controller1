#ifndef SATCOM_HPP
#define SATCOM_HPP

#include <Arduino.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "IridiumSBD.h"



void initialize_satcom_tasks();

bool sendJsonOverSatellite();

void receive_json_satcom();



#endif