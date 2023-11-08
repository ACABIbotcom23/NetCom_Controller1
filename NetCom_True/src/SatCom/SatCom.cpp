#include <SatCom/SatCom.hpp>
#include "Json/Json.hpp"
#include "Semaphore.hpp"
#include "PinDefines/PinDefines.hpp"

const int SEND_WINDOW_START_INTERVAL_MS = 30000;        // 30 seconds for demo, will be 5 minutes
const int SEND_WINDOW_LENGTH_MS = 10000;                // 10 seconds for demo, will be 10 seconds
const int UPDATE_OFFSET_MS = -15000;                    // 15 seconds before the send window
const int UPDATE_TASK_DELAY_MS = SEND_WINDOW_START_INTERVAL_MS + UPDATE_OFFSET_MS;

IridiumSBD isbd(Serial1);

void initialize_satcom_tasks(){

    IridiumSBD isbd(Serial1);
    //xTaskCreate(sendJsonOverSatelliteTask, "sendJsonOverSatelliteTask", 4096, NULL, configMAX_PRIORITIES - 1, NULL);

}
// Im portant notes if no iridium module using the uart port then ESP32 will stroke and reboot
// we still get into function and print the binary string (yay)
bool sendJsonOverSatellite() {
  
    Serial.println("Start of sendJsonOverSatellite");
    uint8_t binaryString[300];
    size_t data_s;
    if (get_json_as_binary_string(binaryString, 300, data_s)){
        //Serial.println(binaryToString(buffer, data_s));
        Serial.println((char*)binaryString);

        int error = isbd.begin();
        if (error != ISBD_SUCCESS){
            Serial.println("begin failed for isbd");
            Serial.println(error);
            return false;
        }
        error = isbd.sendSBDBinary(binaryString, data_s);
        if (error != ISBD_SUCCESS){
            Serial.println("SBD Send Failed");
            Serial.println(error);
            return false;
        }
        //isbd.end();

        return true;

    }
    else{
        Serial.println("Failed to get binary string of json");
        return false;
    }

    return true;

}



// void sendJsonOverSatelliteTask(void *parameter) {
//     Serial.println("Start of sendJsnOverSatelliteTask function");
//     for (;;) {
//         vTaskDelay(pdMS_TO_TICKS(SEND_WINDOW_START_INTERVAL_MS));
//         if (sendJsonOverSatellite()){
//             Serial.println("Message sent over satellite");
//         }
//         else{
//             Serial.println("Message send failed");
//         }
        
//     }
//     Serial.println("End of sendJsnOverSatelliteTask function");
// }