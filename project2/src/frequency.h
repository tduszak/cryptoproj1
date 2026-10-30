#ifndef PROJECT2_FREQUENCY_H
#define PROJECT2_FREQUENCY_H

#include <string>
#include <vector>
#include <array>

namespace project2
{

// Calculates M_g for each possible Caesar shift (0-25)
double calculate_mg(const std::string& substring, int shift);

// Generates a table of M_g values for all seven substrings
void print_frequency_table(const std::vector<std::string>& substrings);

// determines the seven-letter Vigenere keyword
std::string find_keyword(const std::vector<std::string>& substrings);

}

#endif