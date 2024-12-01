#ifndef READER_H
#define READER_H
#include <fstream>
#include <iostream>
#include <string>

const std::string linebreak =
    "\n===== ===== ===== ===== ===== ===== ===== =====\n";

/**
 * asks the user a yes or no question
 *
 * @param[in] string a question
 * @return true if yes, false if no
 */
bool yes_no_prompt(std::string);

/**
 * asks the user for destination
 *
 * @param[in] string a question
 * @return string
 */
std::string destination_prompt(std::string);

/**
 * the main option prompt
 *
 * @return int option
 */
int option_prompt();

#endif