#ifndef JSON_HPP
#define JSON_HPP

#include <ArduinoJson.h>


#include "LittleFS.h"
#include "freertos/task.h"

#define SIZE_OF_JSON_BYTES 300

extern const char *jsonFileName;            // holds all data not sensor data
extern const char *SENSOR_DATA_JSONFILE;    // holds all sensor data only


void init_json();

void checkOrCreateJsonFile();
void updateJsonData(uint8_t batteryLevel, uint8_t statusCode[2], float gpsData[3]);
bool get_json_as_binary_string(uint8_t *binary_string, size_t buffer_size, size_t &data_size);

void updateJsonDataTask(void *parameter);

void reverse_str(char* str, int len);
int int_to_str(int x, char str[], int d);
void ftoa(float n, char* res, int after_dec);

bool delete_file(const char* file_name);

#endif