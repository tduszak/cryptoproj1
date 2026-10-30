#include "coincidence.h"

#include <array>
#include <cmath>
#include <stdexcept>

namespace project2
{

std::vector<std::string> split_substrings(const std::string& ciphertext, std::size_t key_length)
{
    if (key_length == 0 || key_length > ciphertext.size())
    {
        throw std::invalid_argument("Key length must be between 1 and the ciphertext length.");
    }

    std::vector<std::string> substrings(key_length);
    for (std::size_t position = 0; position < ciphertext.size(); ++position)
    {
        const char character = ciphertext[position];
        if (character < 'A' || character > 'Z')
        {
            throw std::invalid_argument("Coincidence analysis requires uppercase A-Z only.");
        }

        // Zero-based column j contains positions j, j + m, j + 2m, and so on.
        substrings[position % key_length] += character;
    }

    return substrings;
}

double index_of_coincidence(const std::string& substring)
{
    if (substring.size() < 2)
    {
        throw std::invalid_argument("Each substring needs at least two letters for an index of coincidence.");
    }

    std::array<std::size_t, 26> frequencies{};
    for (const char character : substring)
    {
        if (character < 'A' || character > 'Z')
        {
            throw std::invalid_argument("Coincidence analysis requires uppercase A-Z only.");
        }
        ++frequencies[static_cast<std::size_t>(character - 'A')];
    }

    // Count matching ordered pairs without replacement, as on course slide 14.
    // Convert before multiplication to avoid integer overflow and truncation.
    long double matching_pairs = 0.0L;
    for (const std::size_t frequency : frequencies)
    {
        if (frequency > 1)
        {
            matching_pairs += static_cast<long double>(frequency) * (frequency - 1);
        }
    }

    const long double length = static_cast<long double>(substring.size());
    return static_cast<double>(matching_pairs / (length * (length - 1.0L)));
}

KeyLengthAnalysis analyze_key_length(const std::string& ciphertext, std::size_t key_length)
{
    const std::vector<std::string> substrings = split_substrings(ciphertext, key_length);
    KeyLengthAnalysis analysis{key_length, {}, 0.0, 0.0, 0.0};
    for (const std::string& substring : substrings)
    {
        const double coincidence_index = index_of_coincidence(substring);
        analysis.substrings.push_back({substring.size(), coincidence_index});
        analysis.mean_index += coincidence_index;
        analysis.mean_distance_from_english += std::abs(coincidence_index - english_coincidence_index);
        analysis.mean_distance_from_random += std::abs(coincidence_index - random_coincidence_index);
    }

    const double substring_count = static_cast<double>(key_length);
    analysis.mean_index /= substring_count;
    analysis.mean_distance_from_english /= substring_count;
    analysis.mean_distance_from_random /= substring_count;
    return analysis;
}

}
