#ifndef SATCOM_HPP
#define SATCOM_HPP

#include <Arduino.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "IridiumSBD.h"



void initialize_satcom_tasks();

void sendJsonOverSatelliteTask(void *parameter);

bool sendJsonOverSatellite();

void receive_json_satcom();

void receive_json_satcom_task(void *parameter);

#endif