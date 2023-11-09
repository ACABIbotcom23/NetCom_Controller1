#include "GNSS/GNSS.hpp"

float GNSS_values_arr[3] = {0.0};

bool get_GNSS(){

}

float get_GNSS_value(uint8_t location){
    return GNSS_values_arr[location];
}