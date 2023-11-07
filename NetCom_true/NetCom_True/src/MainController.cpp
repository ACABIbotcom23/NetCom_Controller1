#include "MainHeader.hpp"
#include "PinDefines.hpp"
#include "Semaphore.hpp"
#include "Json/Json.hpp"
#include "SatCom/SatCom.hpp"

void setup(){
    Serial.begin(9600);

    Serial.println("Start of setup function....");


    init_pins();
    /*
    for the pins in have done something very very wrong with this. to the point where if this is enabled
    the serial monitor shits itself. might try to use arduino's wire.h instead of driver/i2c.h and driver/uart.h
    This is not needed yet.
    */

    if(!init_xsemaphore()){
        Serial.println("Failed to init semapore");
    }

    init_json_tasks();
    initialize_satcom_tasks();
    //initialize_wifi_tasks();

    vTaskStartScheduler();

}

void loop(){

}