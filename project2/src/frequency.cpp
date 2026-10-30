
#include "frequency.h"

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace project2
{

// Standard English letter frequencies, from A through Z (percent).
const std::array<double, 26> english_frequencies = {
    8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0,
    6.1, 7.0, 0.2, 0.8, 4.0, 2.4, 6.7,
    7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8,
    1.0, 2.3, 0.1, 2.0, 0.1
};

// Calculate M_g for one substring and one possible shift.
double calculate_mg(const std::string& substring, int shift)
{
    if (substring.empty() || shift < 0 || shift > 25)
    {
        throw std::invalid_argument("Invalid substring or shift.");
    }

    std::array<int, 26> counts{};

    for (char letter : substring)
    {
        if (letter < 'A' || letter > 'Z')
        {
            throw std::invalid_argument("Substring must contain uppercase A-Z.");
        }
        ++counts[letter - 'A'];
    }

    double mg = 0.0;

    for (int i = 0; i < 26; ++i)
    {
        int shifted_index = (i + shift) % 26;
        double observed_frequency =
            static_cast<double>(counts[shifted_index]) / substring.size();

        mg += english_frequencies[i] * observed_frequency;
    }

    return mg;
}

// Print the 26-row table, with one column per substring.
void print_frequency_table(const std::vector<std::string>& substrings)
{
    std::cout << "\nPart 2 - Frequency Analysis\n\n";
    std::cout << std::setw(6) << "g";

    for (std::size_t j = 0; j < substrings.size(); ++j)
    {
        std::cout << std::setw(10) << ("y" + std::to_string(j + 1));
    }

    std::cout << '\n';

    for (int g = 0; g < 26; ++g)
    {
        std::cout << std::setw(6) << g;

        for (const std::string& substring : substrings)
        {
            std::cout << std::fixed << std::setprecision(2)
                      << std::setw(10) << calculate_mg(substring, g);
        }

        std::cout << '\n';
    }
}

// Find the highest-scoring shift for each substring.
std::string find_keyword(const std::vector<std::string>& substrings)
{
    std::string keyword;

    for (const std::string& substring : substrings)
    {
        int best_shift = 0;
        double best_score = calculate_mg(substring, 0);

        for (int g = 1; g < 26; ++g)
        {
            double score = calculate_mg(substring, g);

            if (score > best_score)
            {
                best_score = score;
                best_shift = g;
            }
        }

        keyword += static_cast<char>('A' + best_shift);
    }

    return keyword;
}

}
