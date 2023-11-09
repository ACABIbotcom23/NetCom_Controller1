#ifndef SATCOM_HPP
#define SATCOM_HPP

#include <Arduino.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "IridiumSBD.h"



void initialize_satcom_tasks();

bool sendJsonOverSatellite(String file);

void receive_json_satcom();

bool check_incoming_message();




#endif