#include "ciphertext.h"
#include "coincidence.h"
#include "frequency.h"
#include "decrypt.h"

#include <algorithm>
#include <array>
#include <exception>
#include <iomanip>
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

        // Calculate everything before printing so invalid input cannot leave a partial report.
        const std::array<project2::KeyLengthAnalysis, 3> analyses{
            project2::analyze_key_length(ciphertext, 6),
            project2::analyze_key_length(ciphertext, 7),
            project2::analyze_key_length(ciphertext, 8)
        };

        std::cout << "MATH 4175 - Cryptography Project 2\n"
                  << "Part 1 - Index of Coincidence\n\n"
                  << "Group 5\n"
                  << "Group Members:\n"
                  << "Nguyen Nguyen\n"
                  << "Spencer Steadman\n"
                  << "Tanishqa Gautam\n"
                  << "Tyler Duszak\n\n"
                  << "Ciphertext characters: " << ciphertext.size() << '\n'
                  << "IC = sum(frequency * (frequency - 1)) / (length * (length - 1))\n"
                  << std::fixed << std::setprecision(9)
                  << "Course benchmarks: English = " << project2::english_coincidence_index
                  << "; uniform random = " << project2::random_coincidence_index << ".\n";

        for (const project2::KeyLengthAnalysis& analysis : analyses)
        {
            std::cout << "\nm = " << analysis.key_length << '\n'
                      << "Substring   Length   Index of coincidence\n";
            for (std::size_t offset = 0; offset < analysis.substrings.size(); ++offset)
            {
                const project2::SubstringAnalysis& substring = analysis.substrings[offset];
                std::cout << std::left << std::setw(12) << ("y" + std::to_string(offset + 1))
                          << std::setw(9) << substring.length << substring.coincidence_index << '\n';
            }
            std::cout << "Mean IC: " << analysis.mean_index << '\n'
                      << "Mean absolute distance from 0.065: " << analysis.mean_distance_from_english << '\n';
        }

        const project2::KeyLengthAnalysis& length_seven = analyses[1];
        // Require a strict preference over both alternatives and over the random benchmark.
        // This is statistical support among the tested lengths, not proof of the actual key.
        const bool supports_seven =
            length_seven.mean_distance_from_english < analyses[0].mean_distance_from_english &&
            length_seven.mean_distance_from_english < analyses[2].mean_distance_from_english &&
            length_seven.mean_distance_from_english < length_seven.mean_distance_from_random;

        std::cout << "\nDoes Part 1 support m = 7? " << (supports_seven ? "Yes.\n" : "No.\n");
        if (supports_seven)
        {
            const auto bounds = std::minmax_element(
                length_seven.substrings.begin(), length_seven.substrings.end(),
                [](const project2::SubstringAnalysis& first, const project2::SubstringAnalysis& second)
                {
                    return first.coincidence_index < second.coincidence_index;
                });
            std::cout << "For m = 7, the individual indices range from "
                      << bounds.first->coincidence_index << " to " << bounds.second->coincidence_index
                      << ", near the English benchmark of 0.065.\n"
                      << "Their mean absolute distance from 0.065 ("
                      << length_seven.mean_distance_from_english
                      << ") is smaller than for m = 6 (" << analyses[0].mean_distance_from_english
                      << ") and m = 8 (" << analyses[2].mean_distance_from_english << ").\n"
                      << "The m = 7 columns are also closer to English than to the uniform-random benchmark.\n";
        }
        else
        {
            std::cout << "The calculated indices do not show a strict preference for m = 7 near the English benchmark.\n";
        }
        
        std::cout << "This is statistical support, not proof of the key length or keyword.\n";

        // part 2: begin by splitting the ciphertext into seven substrings
        const std::vector<std::string> substrings = project2::split_substrings(ciphertext, 7);

        // generates a frequency table
        project2::print_frequency_table(substrings);

        // finds the most likely keyword
        const std::string keyword = project2::find_keyword(substrings);

        std::cout << "\nRecovered keyword: " << keyword << '\n';

        // part 2: use the recovered keyword to decrypt the text
        const std::string plaintext = project2::decrypt(ciphertext, keyword);

        std::cout << "\nPart 3: Decrypted Plaintext\n\n";
        std::cout << plaintext << '\n';

    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
