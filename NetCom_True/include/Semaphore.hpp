#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

extern SemaphoreHandle_t xSemaphore;

bool init_xsemaphore();

#endif