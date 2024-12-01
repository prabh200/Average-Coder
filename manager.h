#ifndef ELLIOT_MAN
#define ELLIOT_MAN
#pragma once
#include "LatLngMap.h"
#include "aqi.h"
#include "maps.h"
#include "reader.h"
#include "quicksort.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

namespace man {
    std::string origin();
    std::string destination();
    std::string getName();
}

namespace main_man{
    void core();
    void sort_cache_entries();
}

#endif