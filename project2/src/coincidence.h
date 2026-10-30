#ifndef CRYPTOPROJ1_PROJECT2_COINCIDENCE_H
#define CRYPTOPROJ1_PROJECT2_COINCIDENCE_H

#include <cstddef>
#include <string>
#include <vector>

namespace project2
{

inline constexpr double english_coincidence_index = 0.065;
inline constexpr double random_coincidence_index = 1.0 / 26.0;

struct SubstringAnalysis
{
    std::size_t length;
    double coincidence_index;
};

struct KeyLengthAnalysis
{
    std::size_t key_length;
    std::vector<SubstringAnalysis> substrings;
    double mean_index;
    double mean_distance_from_english;
    double mean_distance_from_random;
};

// Input must already contain uppercase A-Z only. Invalid lengths or letters throw
// std::invalid_argument; IC is undefined for strings shorter than two characters.
std::vector<std::string> split_substrings(const std::string& ciphertext, std::size_t key_length);
double index_of_coincidence(const std::string& substring);
KeyLengthAnalysis analyze_key_length(const std::string& ciphertext, std::size_t key_length);

}

#endif
