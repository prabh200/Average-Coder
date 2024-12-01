#ifndef ELLIOT_MAP
#define ELLIOT_MAP
#pragma once
#include <iostream>
#include <vector>

#include "data.h"

namespace maps {

std::string generateAddress(std::string origin, std::string destination, bool tolls=true, bool highways=true);

void curl(std::string address);

std::string readRoute();

bool route_fail();

std::vector<float> getLat();
std::vector<float> getLong();

std::vector<float> edges();

dataE::queue*  getMessages();

}

#endif