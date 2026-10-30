
#include "decrypt.h"

#include <stdexcept>

namespace project2
{

// Decrypt Vigenere ciphertext using a repeating keyword.
std::string decrypt(const std::string& ciphertext, const std::string& keyword)
{
    if (keyword.empty())
    {
        throw std::invalid_argument("Keyword cannot be empty.");
    }

    std::string plaintext;

    for (std::size_t i = 0; i < ciphertext.size(); ++i)
    {
        // Convert letters into numbers from 0 to 25.
        int c = ciphertext[i] - 'A';
        int k = keyword[i % keyword.size()] - 'A';

        if (c < 0 || c > 25 || k < 0 || k > 25)
        {
            throw std::invalid_argument("Ciphertext and keyword must be uppercase A-Z.");
        }

        // Vigenere decryption: P = (C - K) mod 26.
        int p = (c - k + 26) % 26;

        // Convert the result back into an uppercase letter.
        plaintext += static_cast<char>('A' + p);
    }

    return plaintext;
}

}
