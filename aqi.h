#ifndef ELLIOT_AQI
#define ELLIOT_AQI
#pragma once
#include "LatLngMap.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

namespace aqi {
    int getAQI(float lat, float lng, LatLngMap &cache, bool refresh_cache);
    std::string aqiPrint(int aqiValue);
    std::string aqiColor(int aqiValue);
    std::string aqiPrintChar(int aqiValue);

}

#endif