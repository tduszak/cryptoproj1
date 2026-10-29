#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

int main(int argument_count, char* argument_values[])
{
    if (argument_count != 2)
    {
        std::cerr << "Usage: project2_vigenere <ciphertext-file>\n";
        return 1;
    }

    std::ifstream input_file(argument_values[1], std::ios::binary);
    if (!input_file)
    {
        std::cerr << "Cannot open ciphertext file: " << argument_values[1] << '\n';
        return 1;
    }

    std::string ciphertext;
    char character = '\0';
    while (input_file.get(character))
    {
        if (character >= 'A' && character <= 'Z')
        {
            ciphertext += character;
        }
        else if (!std::isspace(static_cast<unsigned char>(character)))
        {
            std::cerr << "Ciphertext must contain only A-Z and whitespace.\n";
            return 1;
        }
    }

    if (input_file.bad())
    {
        std::cerr << "Cannot read ciphertext file: " << argument_values[1] << '\n';
        return 1;
    }

    if (ciphertext.empty())
    {
        std::cerr << "Ciphertext must contain at least one uppercase letter.\n";
        return 1;
    }

    std::cout << "Project 2 - Vigenere cipher scaffold\n"
              << "Ciphertext characters: " << ciphertext.size() << '\n'
              << "Status: input validated; cryptanalysis is not implemented.\n";

    return 0;
}
