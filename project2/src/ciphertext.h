#ifndef CRYPTOPROJ1_PROJECT2_CIPHERTEXT_H
#define CRYPTOPROJ1_PROJECT2_CIPHERTEXT_H

#include <string>

namespace project2
{

// Return uppercase letters with whitespace removed; throw std::runtime_error for
// missing, unreadable, empty, or invalid input so callers cannot use partial data.
std::string read_ciphertext(const std::string& path);

}

#endif
