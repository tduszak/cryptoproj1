#include "ciphertext.h"

#include <exception>
#include <iostream>
#include <string>

int main(int argument_count, char* argument_values[])
{
    // Resolve the caller's input path rather than embedding a machine-specific path.
    if (argument_count != 2)
    {
        std::cerr << "Usage: project2_vigenere <ciphertext-file>\n";
        return 1;
    }

    try
    {
        const std::string ciphertext = project2::read_ciphertext(argument_values[1]);

        // Report readiness only; the assignment's cryptanalysis is not implemented yet.
        std::cout << "Project 2 - Vigenere cipher scaffold\n"
                  << "Ciphertext characters: " << ciphertext.size() << '\n'
                  << "Status: input validated; cryptanalysis is not implemented.\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
