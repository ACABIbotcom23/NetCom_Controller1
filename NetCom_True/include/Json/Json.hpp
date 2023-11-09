#ifndef JSON_HPP
#define JSON_HPP

#include <ArduinoJson.h>


#include "LittleFS.h"
#include "freertos/task.h"

#define SIZE_OF_JSON_BYTES 300

extern const char *jsonFileName;            // holds all data not sensor data
extern const char *RECEIVE_DATA_JSONFILE;
extern const char *SENSOR_DATA_JSONFILE;    // holds all sensor data only


extern String send_file;
extern String receive_file;

void init_json();
void init_test_data();


void create_Status_Doc();
void create_Receive_Doc();
void create_Sensor_Doc();


void update_json(uint8_t file_number);

void check_create_json();
//void updateJsonData(uint8_t batteryLevel, uint8_t statusCode[2], float gpsData[3]);
bool get_json_as_binary_string(uint8_t *binary_string, size_t buffer_size, size_t &data_size);
//bool get_json_as_binary_string(void *parameter);

// replace this with proper get data function
void get_test_data(void *parameter);

void reverse_str(char* str, int len);
int int_to_str(int x, char str[], int d);
void ftoa(float n, char* res, int after_dec);

bool delete_file(const char* file_name);

void stringToByteArray(const String& inputString, byte* byteArray, size_t& byteArraySize);

#endif