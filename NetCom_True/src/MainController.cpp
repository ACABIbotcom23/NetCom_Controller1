#include "MainHeader.hpp"
#include "PinDefines/PinDefines.hpp"
//#include "Semaphore.hpp"
#include "Json/Json.hpp"
#include "SatCom/SatCom.hpp"
#include "GNSS/GNSS.hpp"

void setup(){
    Serial.begin(9600);

    Serial.println("Start of setup function....");


    init_pins();

    init_json();
    initialize_satcom_tasks();
    //initialize_wifi_tasks();

    // init_GNSS();    

}

void loop(){
    // all functions are on core 1 unless stated other wise

    // will check if there is a message every 10 seconds?
    // if we set satellite on core 0 then we can speed up the main loop
    // check if there is available message (try core 0 but can be on 1)
        // if yes store file in string
        // convert to json
        // parse json
        // send data to controller 2
    // gather GNSS data
        // if no gnss received after 5ms add error 
        // code to status for next json status send
        // repeat last GNSS reading to mark current stopped location
    // gather battery data
        // if no gnss received after 5ms add error 
        // code to status for next json status send
        // set battery_level to 0 or -1
    // have status doc send every 5 minutes on core 0
    // after status doc was sent, send sensor data on core 0
        // get data from controller 2
        // create json for sensor
        // place 300 bytes of data into json
        // convert json to binary array
        // send over satellite
        // this will take roughly 2 minutes to complete
        // 10 cycles / files
    
    // this is alternative idea for sensor file where we send every 300 seconds
    // check if sensor data is ready first 300 bytes
        // if yes get data from controller 2
        // create json for sensor
        // place 300 bytes of data into json
        // convert json to binary array
        // send over satellite

    if (check_incoming_message()){
        // call function to read message and store in a string
        // sonvert string to json
        // parse string for data
        // send data to controller 2
            // need to recieve ack from contoller 2 so it knows 
            // that waypoint can be calculated

    }
    // if no message in mailbox then tell controlller 2 to stay in place
    // record sensor data still
    // this communication will be a string of strings over i2c
    // will be string for movment, command for stop and go with coordinates.

    //if (get_GNSS())
    // need to know gnss using
    // gather GNSS data
        // if NO gnss received after 5ms add error 
        // code to status for next json status send
        // repeat last GNSS reading to mark current stopped location
        // if YES add GNSS to DATA struct
    // using i2c try to get battery
        // if i2c failed try again and again
        // if failed 3 times then place error code in status
        // array in DATA struct
        // if i2c SUCCESS read data
        // add data to DATA struct
        // if data is not changing from previous reading 5 minutes prior
        // add error message to staus
    // at 5 minutes ask controller 2 for sensor data    
    // if no response after 3 tries add error to status 
    // if yes response receive all 3000 bytes of data in array
        // place array in DATA struct 2
        // seperate data so that each part gets around 50 values
        // add first 50 into the file
        // serialized json and convert to byte array
        // send over satellite
        // repeat until all 3000 bytes are sent. 
        // as mentioned above this will take around 2 minutes because
        // of a 10 second delay
}