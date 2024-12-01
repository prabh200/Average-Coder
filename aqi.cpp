#include "aqi.h"
#include "LatLngMap.h"
#include <fstream>
#include <stdlib.h>
#include <unistd.h>

int aqi::getAQI(float lat, float lng, LatLngMap &cache, bool refresh_cache) {
    // check if its in the hash
    // if it is, use that data instead!!!
    // otherwise, add it to the file + the hash.

    std::string x = std::to_string(lng);
    std::string y = std::to_string(lat);

    std::string hash_key =
        y.substr(0, y.length() - 5) + "_" + x.substr(0, x.length() - 5);

    if (!refresh_cache) {
        int cachedData = cache.find(hash_key);
        if (cachedData != -2) {
            return cachedData;
        }
    }

    // Creates a file "aqi" containing the data from the provided coordinates.
    
    std::string address = "http://api.openweathermap.org/data/2.5/air_pollution?lat="
                        + std::to_string(lat) + "&lon=" + std::to_string(lng)
                        + "&appid=a6d0f7910d7576a3e9186234c574fe89";
    
    std::string command = "curl \"" + address + "\" -s -o data/aqi";
    
    int ignoredReturnValue;
    ignoredReturnValue = system(command.c_str());
    
    // Returns the data in the "aqi" file.
    int aqi = -1; // Will return -1 if failing to find AQI value.
    std::ifstream file;
    file.open("./data/aqi");
    std::string data;
    bool inSteps = false;
    while (file >> data) {
        for (int i = 0; i < data.length() - 5; i++) {
            if (data[i] == 'a' && data[i + 1] == 'q' && data[i + 2] == 'i') {
                aqi = data[i + 5] - '0'; // I can't believe that this actually works...
            }
        }
    }
    file.close();
    
    cache.insert(hash_key, aqi); // Add the new location to the cache.

    // TODO: Add the new location to the cache file.

    return aqi;
}

std::string aqi::aqiPrint(int aqiValue) {

    switch (aqiValue) {
        case -1: return "No Data";
        case 1: return "\033[;32m          Good (5/5)\033[0m\n";
        case 2: return "\033[;36m          Fair (4/5)\033[0m\n";
        case 3: return "\033[;33m          Moderate (3/5)\033[0m\n";
        case 4: return "\033[;35m          Poor (2/5)\033[0m\n";
        case 5: return "\033[;31m          VeryPoor (1/5)\033[0m\n";
        default: return "Undefined AQI Level";
  }
}

std::string aqi::aqiPrintChar(int aqiValue) {

    switch (aqiValue) {
        case -1: return "0";
        case 1: return "\033[;32m5\033[0m";
        case 2: return "\033[;36m4\033[0m";
        case 3: return "\033[;33m3\033[0m";
        case 4: return "\033[;35m2\033[0m";
        case 5: return "\033[;31m1\033[0m";
        default: return "X";
  }
}
std::string aqi::aqiColor(int aqiValue) {

    switch (aqiValue) {
        case -1: return "Color 07";
        case 1: return "Color 02";
        case 2: return "Color 0A";
        case 3: return "Color 06";
        case 4: return "Color 0C";
        case 5: return "Color 04";
        default: return "Color 07";
  }
}