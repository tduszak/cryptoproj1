#include "ciphertext.h"

#include <cctype>
#include <fstream>
#include <stdexcept>

namespace project2
{

std::string read_ciphertext(const std::string& path)
{
    std::ifstream input_file(path, std::ios::binary);
    if (!input_file)
    {
        throw std::runtime_error("Cannot open ciphertext file: " + path);
    }

    std::string ciphertext;
    char character = '\0';
    while (input_file.get(character))
    {
        if (character >= 'A' && character <= 'Z')
        {
            ciphertext += character;
        }
        // PDF line wrapping must not change character positions in later analysis.
        // The unsigned cast keeps cctype calls valid for non-ASCII input bytes.
        else if (!std::isspace(static_cast<unsigned char>(character)))
        {
            throw std::runtime_error("Ciphertext must contain only A-Z and whitespace.");
        }
    }

    // Do not accept a partial message when a read fails before the end of the file.
    if (input_file.bad())
    {
        throw std::runtime_error("Cannot read ciphertext file: " + path);
    }

    if (ciphertext.empty())
    {
        throw std::runtime_error("Ciphertext must contain at least one uppercase letter.");
    }

    return ciphertext;
}

}
