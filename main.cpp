#include "manager.h"
#include "reader.h"
#include <iomanip>
#include <iostream>

int main() {
    // system("Color 07");
    // Gets users name
    std::string userName = man::getName();

    std::cout << "\nWelcome " << userName << "!\n"; // Greets user

    std::cout
      << "This program is designed to map the optimal way to reach a "
         "destination. It includes distance traveled, cost of travel, and AQI "
         "index to give you the fastest, cheapest, and cleanest path.\n";

    bool proceed = yes_no_prompt("\nPlease enter Y/y to continue, N/n to quit: ");

    while (proceed) {
        std::cout << linebreak;
        switch(option_prompt()) {
            case 1: main_man::core(); break;
            case 2: main_man::sort_cache_entries(); break;
        }
        proceed = yes_no_prompt("Continue using the program?\nY/y to continue, N/n to quit: ");
    }
    std::cout << linebreak << "Program Ended" << linebreak;
    return 0;
}