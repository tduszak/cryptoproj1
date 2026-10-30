
#ifndef PROJECT2_DECRYPT_H
#define PROJECT2_DECRYPT_H

#include <string>

namespace project2
{

// Decrypt uppercase Vigenere ciphertext using the recovered keyword.
std::string decrypt(const std::string& ciphertext, const std::string& keyword);

}

#endif
