#include "reader.h"

const std::string invalid_input_alert =
    "\n\t!!! Invalid, please re-enter. !!!\n";

bool yes_no_prompt(std::string prompt) {
  char c = 0;

  std::cout << prompt;
  std::cin >> c;

  // clear the input buffer
  std::cin.clear();
  std::cin.ignore(4096, '\n');

  // reprompt until input is good
  while (tolower(c) != 'y' && tolower(c) != 'n') {
    std::cout << invalid_input_alert;
    std::cout << std::endl << prompt;
    std::cin >> c;

    // clear the input buffer
    std::cin.clear();
    std::cin.ignore(4096, '\n');
  }

  // case insensitive check
  // y return true, n return false
  if (tolower(c) == 'y') {
    return true;
  }
  return false;
}

std::string destination_prompt(std::string prompt) {
  std::cout << prompt;

  std::string address;
  std::getline(std::cin, address);

  // clear input buffer
  std::cin.clear();

  return address;
};

int option_prompt() {
    std::cout << "Choose one option below.\n"
                "\t1. Run the Core Program\n"
                "\t2. Sort the Cache Table Data Entries\n";
    int option = 0;
    std::cout << "Enter your option: ";
    std::cin >> option;

    // clear the input buffer
    std::cin.clear();
    std::cin.ignore(4096, '\n');

    while (option <= 0 && option > 2) {
        std::cout << invalid_input_alert;
        std::cout << "Enter your option: ";
        std::cin >> option;
        
        // clear the input buffer
        std::cin.clear();
        std::cin.ignore(4096, '\n');
    }
    return option;
}