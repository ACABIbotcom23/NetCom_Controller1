#include "Json/Json.hpp"
#include "Semaphore.hpp"
#include "TestData.hpp"
#include "PinDefines/PinDefines.hpp"

const int SEND_WINDOW_START_INTERVAL_MS = 30000;        // 30 seconds for demo, will be 5 minutes
const int SEND_WINDOW_LENGTH_MS = 10000;                // 10 seconds for demo, will be 10 seconds
const int UPDATE_OFFSET_MS = -14000;                    // 14 seconds before the send window
const int UPDATE_TASK_DELAY_MS = SEND_WINDOW_START_INTERVAL_MS + UPDATE_OFFSET_MS;

StaticJsonDocument<SIZE_OF_JSON_BYTES> Status_Doc;

String send_file = "";

const char *jsonFileName = "/send_file.json"; 

StaticJsonDocument<SIZE_OF_JSON_BYTES> Receive_Doc;

String receive_file = "";

const char *RECEIVE_DATA_JSONFILE = "/receive_file.json";
/*
need to figure out a function structure for the 16 bit and to see how fast we can
transfer 50 16 bit numbers into a file 30 times. 
can explain more if asked but essentially the rockblock can only send 340 bytes at max and 300 bytes will fit about
50 16bit numbers.300 is chosen because we need to be safe with the possible overhead of a json file and 40 bytes is not enough to save anything

StaticJsonDocument<300> Sensor_Doc;

const char *SENSOR_DATA_JSONFILE = "/sensor_doc.json";
*/

send_data_1 TEST_DATA_1;

void init_test_data(){
    TEST_DATA_1.Battery_Level = 100;
    TEST_DATA_1.Status_Code[0] = 99;
    TEST_DATA_1.Status_Code[1] = 98;
    TEST_DATA_1.GPS_Data[0] = 33.8;
    TEST_DATA_1.GPS_Data[1] = 35.7;
    TEST_DATA_1.GPS_Data[2] = 9.21;
}

void init_json(){

    init_test_data();

    create_Status_Doc();

    create_Receive_Doc();

    create_Sensor_Doc();

}

void create_Status_Doc(){
    Status_Doc["DOC_ID"] = "Status Doc";
    Status_Doc["Battery_Level"] = 0;
    Status_Doc["Status_Code"][0] = 0;
    Status_Doc["Status_Code"][1] = 0;
    Status_Doc["GPS_Data"][0] = 0.0;
    Status_Doc["GPS_Data"][1] = 0.0;
    Status_Doc["GPS_Data"][2] = 0.0;

    serializeJson(Status_Doc, send_file);
}

// this is template but will need to confirm what exactly is in each file received
void create_Receive_Doc(){
    Receive_Doc["DOC_ID"] = "Receive Doc";
    Receive_Doc["Battery_Level"] = 0;
    Receive_Doc["Status_Code"][0] = 0;
    Receive_Doc["Status_Code"][1] = 0;
    Receive_Doc["GPS_Data"][0] = 0.0;
    Receive_Doc["GPS_Data"][1] = 0.0;
    Receive_Doc["GPS_Data"][2] = 0.0;

    serializeJson(Receive_Doc, receive_file);
}

void create_Sensor_Doc(){


}

void update_json(uint8_t file_number){

    switch (file_number){

        case 0:
            Status_Doc.clear();
            Status_Doc["DOC_ID"] = "Status Doc";
            Status_Doc["Battery_Level"] = TEST_DATA_1.get_battery_level();
            Status_Doc["Status_Code"][0] = TEST_DATA_1.get_status_code(0);
            Status_Doc["Status_Code"][1] = TEST_DATA_1.get_status_code(1);
            Status_Doc["GPS_Data"][0] = TEST_DATA_1.get_gnss_data(0);
            Status_Doc["GPS_Data"][1] = TEST_DATA_1.get_gnss_data(1);
            Status_Doc["GPS_Data"][2] = TEST_DATA_1.get_gnss_data(2);
            break;

        // this is template but will need to confirm what exactly is in each file received
        case 1:
            Receive_Doc.clear();
            Receive_Doc["DOC_ID"] = "Receive Doc";
            Receive_Doc["Battery_Level"] = TEST_DATA_1.get_battery_level();
            Receive_Doc["Status_Code"][0] = TEST_DATA_1.get_status_code(0);
            Receive_Doc["Status_Code"][1] = TEST_DATA_1.get_status_code(1);
            Receive_Doc["GPS_Data"][0] = TEST_DATA_1.get_gnss_data(0);
            Receive_Doc["GPS_Data"][1] = TEST_DATA_1.get_gnss_data(1);
            Receive_Doc["GPS_Data"][2] = TEST_DATA_1.get_gnss_data(2);
            break;

        case 2:
            break;

        default:
            break;
    }

}

void stringToByteArray(const String& inputString, byte* byteArray, size_t& byteArraySize) {
  byteArraySize = inputString.length(); // Set the size of the array
  
  // Fill the byte array with the string's ASCII values
  for (size_t i = 0; i < byteArraySize; i++) {
    byteArray[i] = static_cast<byte>(inputString[i]);
  }

  Serial.print("Byte Array in HEX: ");
  for (size_t i = 0; i < byteArraySize; i++) {
    if(byteArray[i] < 0x10) Serial.print("0"); // Print leading zero for single digit hex
    Serial.print(byteArray[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}
