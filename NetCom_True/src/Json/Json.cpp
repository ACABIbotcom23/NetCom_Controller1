#include "Json/Json.hpp"
#include "Semaphore.hpp"
#include "TestData.hpp"

const int SEND_WINDOW_START_INTERVAL_MS = 30000;        // 30 seconds for demo, will be 5 minutes
const int SEND_WINDOW_LENGTH_MS = 10000;                // 10 seconds for demo, will be 10 seconds
const int UPDATE_OFFSET_MS = -14000;                    // 14 seconds before the send window
const int UPDATE_TASK_DELAY_MS = SEND_WINDOW_START_INTERVAL_MS + UPDATE_OFFSET_MS;

StaticJsonDocument<SIZE_OF_JSON_BYTES> Status_Doc;

const char *jsonFileName = "/send_file.json"; 

/*
need to figure out a function structure for the 16 bit and to see how fast we can
transfer 50 16 bit numbers into a file 30 times. 
can explain more if asked but essentially the rockblock can only send 340 bytes at max and 300 bytes will fit about
50 16bit numbers.300 is chosen because we need to be safe with the possible overhead of a json file and 40 bytes is not enough to save anything

StaticJsonDocument<300> Sensor_Doc;

const char *SENSOR_DATA_JSONFILE = "/sensor_doc.json";
*/

void init_json_tasks(){

    TEST_DATA_1.Battery_Level = 1;
    TEST_DATA_1.Status_Code[0] = 99;
    TEST_DATA_1.Status_Code[1] = 98;
    TEST_DATA_1.GPS_Data[0] = 33.8;
    TEST_DATA_1.GPS_Data[1] = 35.7;
    TEST_DATA_1.GPS_Data[2] = 9.21;


    if (!LittleFS.begin(true)) {
        Serial.println("An error has occurred while mounting SPIFFS");
        return;
    }
    //xTaskCreate(checkOrCreateJsonFileTask, "CheckCreateJson", 4096, NULL, configMAX_PRIORITIES - 1, NULL);
    checkOrCreateJsonFile();

    xTaskCreate(updateJsonDataTask, "UpdateData", 4096, NULL, 1, NULL);

}

void updateJsonDataTask(void *parameter) {
    // swap out with update function
    for (;;) {
        vTaskDelay(pdMS_TO_TICKS(UPDATE_TASK_DELAY_MS));
        // Here you would get your actual new data
        uint8_t newBatteryLevel = 0;
        uint8_t newStatusCode[2] = {0};
        float newGpsData[3] = {0};

        newBatteryLevel = TEST_DATA_1.Battery_Level;    
        
        newStatusCode[0] = TEST_DATA_1.Status_Code[0];   
        newStatusCode[1] = TEST_DATA_1.Status_Code[1];           

        newGpsData[0] = TEST_DATA_1.GPS_Data[0];
        newGpsData[1] = TEST_DATA_1.GPS_Data[1];
        newGpsData[2] = TEST_DATA_1.GPS_Data[2];                                                      
    
        updateJsonData(newBatteryLevel, newStatusCode, newGpsData);
    }
    Serial.println("End of updateJsonTask function");
}

void checkOrCreateJsonFile() {
    Serial.println("Checking or creating JSON file...");

    if (!LittleFS.begin()) {
        Serial.println("An error has occurred while mounting LittleFS");
        return;
    }

    if(LittleFS.exists(jsonFileName)){
        if (delete_file(jsonFileName)){
            Serial.println("yay");
        }
    }

    Status_Doc["Battery_Level"] = 0;
    Status_Doc["Status_Code"][0] = 0;
    Status_Doc["Status_Code"][1] = 0;
    Status_Doc["GPS_Data"][0] = 0.0;
    Status_Doc["GPS_Data"][1] = 0.0;
    Status_Doc["GPS_Data"][2] = 0.0;

    File file = LittleFS.open(jsonFileName, "w");
    if (!file) {
        Serial.println("There was an error opening the file for writing");
        return;
    }

    if (serializeJson(Status_Doc, file) == 0) {
        Serial.println("Failed to write to file");
    }
    else{
        Serial.println("wrote to");
    }
    file.close();
    
    Serial.println("End of checkOrCreateJsonFile function");
}

void updateJsonData(uint8_t batteryLevel, uint8_t statusCode[2], float gpsData[3]) {
    if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE) {
        File file = LittleFS.open(jsonFileName, "r+");
        if (!file) {
            Serial.println("Failed to open file for updating");
            xSemaphoreGive(xSemaphore);
            return;
        }
        
        else {
            
            // Update the fields with new data
            Status_Doc.clear();
            char gps_1[10];
            char gps_2[10];
            char gps_3[10];
            ftoa(gpsData[0], gps_1, 2);
            ftoa(gpsData[1], gps_2, 2);
            ftoa(gpsData[2], gps_3, 2);

            Status_Doc["Battery_Level"] = batteryLevel;
            Status_Doc["Status_Code"][0] = statusCode[0];
            Status_Doc["Status_Code"][1] = statusCode[1];
            Status_Doc["GPS_Data"][0] = gps_1;
            Status_Doc["GPS_Data"][1] = gps_2;
            Status_Doc["GPS_Data"][2] = gps_3;

        }

        file.seek(0); // Go to the start of the file
        if (serializeJson(Status_Doc, file) == 0) {
            Serial.println(F("Failed to write to file"));
        }
        //file.truncate(); // Remove any leftover data
        //serializeJsonPretty(Status_Doc, Serial);
        file.close();

        xSemaphoreGive(xSemaphore);
    } 
    else {
        Serial.println("Could not obtain the semaphore for updating data.");
    }
    Serial.println("End of updateJsonData function");
}



bool get_json_as_binary_string(uint8_t *binary_string, size_t buffer_size, size_t &data_size){

    File file = LittleFS.open(jsonFileName, "r");

    if (!file) {
        Serial.println("Failed to open file for reading");
        return false;
    }

    size_t file_size = file.size();

    // Ensure the caller has provided a buffer large enough for the file content and a null terminator
    if (buffer_size < file_size + 1) {
        Serial.println("Buffer too small for file content");
        file.close(); // Always close the file if you're exiting early
        return false;
    }

    // Read the file into the buffer provided by the caller
    data_size = file.read(binary_string, file_size);

    // Null-terminate the buffer to treat it as a C-string
    binary_string[data_size] = '\0';

    // Close the file as we no longer need it
    file.close();

    // Check if read was successful
    if (data_size != file_size) {
        Serial.println("Failed to read the full file");
        return false;
    }

    return true;
}

bool delete_file(const char* file_name){
    if (LittleFS.remove(file_name)){
        Serial.println("File was deleted");
        return true;
    }
    else{
        Serial.println("File was NOT deleted");
        return false;
    }
}

void reverse_str(char* str, int len){
    int i = 0, j = len - 1, temp;
    while (i < j){
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

int int_to_str(int x, char str[], int d){
    int i = 0;
    while (x){
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
    while (i < d){
        str[i++] = '0';
    }
    reverse_str(str, i);
    str[i] = '\0';
    return i;
}

void ftoa(float n, char* res, int after_dec){
    int ipart = (int)n;
    float fpart = n - (float)ipart;
    int i = int_to_str(ipart, res, 0);
    if (after_dec != 0){
        res[i] = '.';
        fpart = fpart * pow(10, after_dec);
        int_to_str((int)fpart, res + i + 1, after_dec);
    }
}