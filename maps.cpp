#include "maps.h"
#include <fstream>

std::string maps::generateAddress(std::string origin, std::string destination, bool tolls, bool highways) {
    //Takes an origin address, a destination address, booleans for toll and highway usage, and returns the address to the API call.
    std::string uOrigin = origin;
    origin = "";
    for (int i = 2; i < uOrigin.length(); i++){
        if (uOrigin[i] == ' '){
            origin += "%2B";
        }
        else {
            origin += uOrigin[i];
        }
    }

    std::string uDestination = destination;
    destination = "";
    for (int i = 2; i < uDestination.length(); i++){
        if (uDestination[i] == ' '){
            destination += "%2B";
        }
        else {
            destination += uDestination[i];
        }
    }
    
    std::string address = "https://maps.googleapis.com/maps/api/directions/json?origin=" + origin + "&destination=" + destination + "&key=AIzaSyCvY8kGhtd9d-gibzGj2lQ3sGt77U5a2Dw&units=imperial";
    if ((!tolls) && (!highways)){
        address += "&avoid=tolls|highways";
    }
    else if (!highways){
        address += "&avoid=highways";
    }
    else if (!tolls){
        address += "&avoid=tolls";
    }

    return address;    
}

void maps::curl(std::string address){
    //Creates a file "route" containing the data from the provided address.
    std::string command = "curl \"" + address + "\" -s -o data/route";

    int ignoreThisAlso;
    ignoreThisAlso = system(command.c_str());
}

std::string maps::readRoute(){
    //Returns the data in the "route" file.
    std::ifstream route;
    route.open("./data/route");
    std::string routeData;
    std::string allData = "";
    while (route >> routeData) {
        allData += routeData;
    }
    route.close();
    return allData;
}

bool maps::route_fail() {
    std::ifstream route;
    route.open("./data/route");
    std::string s;
    while (route >> s) {
        if (s == "\"ZERO_RESULTS\"") {
            return true;
        }
    }
    return false;
}

std::vector<float> maps::getLat(){
    std::vector<float> latitude;
    std::ifstream route;
    route.open("./data/route");
    std::string routeData;
    bool inSteps = false;
    while (route >> routeData) {
        if (!inSteps) {
            //There is location data before steps that we don't want to read.
            if (routeData == "\"steps\"") { inSteps = true;}
        }
        else {
            if (routeData == "\"lat\"") {
                route >> routeData; // For colon
                route >> routeData; // The latitude is the second item after "lat".
                latitude.push_back(std::stof(routeData));
            }
        }
    }
    route.close();
    return latitude;
}

std::vector<float> maps::getLong(){
    std::vector<float> longitude;
    std::ifstream route;
    route.open("./data/route");
    std::string routeData;
    bool inSteps = false;
    while (route >> routeData) {
        if (!inSteps) {
            //There is location data before steps that we don't want to read.
            if (routeData == "\"steps\"") { inSteps = true;}
        }
        else {
            if (routeData == "\"lng\"") {
                route >> routeData; // For colon
                route >> routeData; // The longitude is the second item after "lng".
                longitude.push_back(std::stof(routeData));
            }
        }
    }
    route.close();
    return longitude;
}

dataE::queue* maps::getMessages(){
    dataE::queue *messageQ = new dataE::queue;
    std::ifstream route;
    route.open("./data/route");
    std::string routeData;
    std::string message = "";
    bool onDistance = false;
    while (route >> routeData) {
        if (routeData == "\"distance\""){
            onDistance = true;
        }
        if (routeData == "\"duration\""){
            onDistance = false;
        }
        if (routeData == "\"text\"") {
            route >> routeData; // For colon
            do {
            route >> routeData; //Grab data until we hit the end of the message
            message += routeData + " ";
            } while (!(routeData[routeData.length() - 1] == ',' && routeData[routeData.length() - 2] == '"'));

            std::string newMessage = "";
            for (int i = 0; i < message.length(); i++){
                if (i == 0){} //Start of message is "
                else if (i >= message.length() - 3){} //End of message is ",
                else{
                    newMessage += message[i];
                }
            }

            messageQ->push(newMessage);
            message = "";
        }
        
        if (routeData == "\"html_instructions\"") {
            route >> routeData; // For colon
            do {
            route >> routeData; //Grab data until we hit the end of the message
            message += routeData + " ";
            } while (!(routeData[routeData.length() - 1] == ',' && routeData[routeData.length() - 2] == '"'));

            std::string newMessage = "";
            for (int i = 0; i < message.length(); i++){
                if (i == 0){} //Start of message is "
                else if (i >= message.length() - 3){} //End of message is ",
                else if (message[i] == '\\'){
                    if (message[i + 6] == '/'){
                        i += 13; //End of bold tag
                    }
                    else{
                        i += 12; //Start of bold tag
                    }
                }
                else{
                    newMessage += message[i];
                }
            }

            messageQ->push(newMessage);
            message = "";
        }
    }
    route.close();
    return messageQ;
}


std::vector<float> maps::edges(){
    std::vector<float> data;
    std::ifstream route;
    route.open("./data/route");
    std::string routeData;
    int i = 0;
    while (i < 4){
        route >> routeData;
        if (routeData == "\"lng\"") {
            route >> routeData; // For colon
            route >> routeData; // The longitude is the second item after "lng".
            data.push_back(std::stof(routeData));
            i++;
        }
        if (routeData == "\"lat\"") {
            route >> routeData; // For colon
            route >> routeData; // The latitude is the second item after "lat".
            data.push_back(std::stof(routeData));
            i++;
        }
    }
    route.close();
    return data;
}
