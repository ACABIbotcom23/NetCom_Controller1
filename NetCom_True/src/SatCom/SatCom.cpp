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

}

// Important notes if no iridium module using the uart port then ESP32 will stroke and reboot

bool sendJsonOverSatellite(String file) {

    byte* byteArray = new byte[file.length()];
    size_t byte_arr_size = 0;

    stringToByteArray(file, byteArray, byte_arr_size);

    Serial.println("Start of sendJsonOverSatellite");

    int error = isbd.begin();
    if (error != ISBD_SUCCESS){
        Serial.println("begin failed for isbd");
        Serial.println(error);
        return false;
    }
    error = isbd.sendSBDBinary(byteArray, byte_arr_size);
    if (error != ISBD_SUCCESS){
        Serial.println("SBD Send Failed");
        Serial.println(error);
        return false;
    }

    delete[] byteArray;
    return true;

}

bool check_incoming_message(){

    if  (isbd.isAsleep()){
        digitalWrite(SLEEP_PIN_Sat, HIGH);
    }
    
    int signal_quality = 0;
    int error = isbd.getSignalQuality(signal_quality);

    if (error != ISBD_SUCCESS){
        Serial.print("Signal quality check failed: error code ");
        Serial.println(error);
        return false;
    }

    if (signal_quality > 0) {
    int messageWaitingCount = 0;
    messageWaitingCount = isbd.getWaitingMessageCount();

        if (messageWaitingCount > 0){
            Serial.println("There is a message waiting to be received.");
            return true;
        }
        else{
            Serial.println("There are no messages waiting or wrror with checking.");
            return false;
        }
    } 
    else {
        Serial.println("Signal quality is too poor to check for messages.");
        return false;
    }

    digitalWrite(SLEEP_PIN_Sat, LOW);
}

