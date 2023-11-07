#include "Semaphore.hpp"

SemaphoreHandle_t xSemaphore = xSemaphoreCreateMutex();

bool init_xsemaphore(){
    
    if (xSemaphore == NULL) {
        return false;
    }
    return true;
}