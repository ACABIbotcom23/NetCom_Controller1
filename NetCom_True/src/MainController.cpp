#include "MainHeader.hpp"
#include "PinDefines/PinDefines.hpp"
//#include "Semaphore.hpp"
#include "Json/Json.hpp"
#include "SatCom/SatCom.hpp"

void setup(){
    Serial.begin(9600);

    Serial.println("Start of setup function....");


    init_pins();


    init_json();
    initialize_satcom_tasks();
    //initialize_wifi_tasks();

    

}

void loop(){

    /*
    
    if no current misson wait in place
        collect sensor data 
        collect battery data
        collect gnss data




    check if there are messages to receive
        if yes receive message and parse
        if no move on
        this shopuld only checkl every 
    
    */

}