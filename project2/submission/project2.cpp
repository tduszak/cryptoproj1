// MATH 4175 - Cryptography Project 2, Group 5
// Participants: Nguyen Nguyen; Spencer Steadman; Tanishqa Gautam; Tyler Duszak
// Compile: c++ -std=c++17 project2.cpp -o project2
// Run: ./project2 (uses the included assignment ciphertext).
// An optional ciphertext file may be supplied as the only argument.
// The accompanying PDF adds readable word spacing and punctuation to Part 3.
// Generated from the modular sources by scripts/prepare_submission.py.
#define PROJECT2_EMBEDDED_SUBMISSION


// ---- ciphertext.h ----
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


// ---- coincidence.h ----
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


// ---- frequency.h ----
#ifndef PROJECT2_FREQUENCY_H
#define PROJECT2_FREQUENCY_H

#include <string>
#include <vector>
#include <array>

namespace project2
{

// Calculates M_g for each possible Caesar shift (0-25)
double calculate_mg(const std::string& substring, int shift);

// Generates a table of M_g values for all seven substrings
void print_frequency_table(const std::vector<std::string>& substrings);

// determines the seven-letter Vigenere keyword
std::string find_keyword(const std::vector<std::string>& substrings);

}

#endif

// ---- decrypt.h ----

#ifndef PROJECT2_DECRYPT_H
#define PROJECT2_DECRYPT_H

#include <string>

namespace project2
{

// Decrypt uppercase Vigenere ciphertext using the recovered keyword.
std::string decrypt(const std::string& ciphertext, const std::string& keyword);

}

#endif


// ---- ciphertext.cpp ----

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


// ---- coincidence.cpp ----

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


// ---- frequency.cpp ----


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
    std::cout << "Table entries are 100 * M_g (percentage scale).\n";
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


// ---- decrypt.cpp ----


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


// ---- main.cpp ----

#include <algorithm>
#include <array>
#include <exception>
#include <iomanip>
#include <iostream>
#include <string>

namespace
{

// Reuse the same calculations and presentation in the modular and submitted programs.
void print_report(const std::string& ciphertext)
{
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

        // Part 3 uses the recovered keyword, not a hardcoded answer.
        const std::string plaintext = project2::decrypt(ciphertext, keyword);

        std::cout << "\nPart 3: Decrypted Plaintext\n\n";
        std::cout << plaintext << '\n';
}

}

// The single-file submission supplies its own entry point with embedded input.
#ifndef PROJECT2_EMBEDDED_SUBMISSION
int main(int argument_count, char* argument_values[])
{
    if (argument_count != 2)
    {
        std::cerr << "Usage: project2_vigenere <ciphertext-file>\n";
        return 1;
    }

    try
    {
        print_report(project2::read_ciphertext(argument_values[1]));
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
#endif


int main(int argument_count, char* argument_values[])
{
    const std::string embedded_ciphertext =
        "LAVHEBSJMDINFGXCLWTUUWARWBQWFTEHWUDDTCAAKKTXTSMYALMVHTAHJHKICFAFZKLEXA"
        "TXIXYMFVLVGUDALRFJTTGKXNLOYOWLVVVQAFKVGEZLEHEXHEZGPVZEDOWARZEAFSGVASOS"
        "DXJIEZESBEWTDWSFGVOPMUMJENPKWKMMCQKVXJMGZWVBEEWMQLARXGUNWLLWEDKKHCICAF"
        "LKFPOHWJTTGEEKLHKLEUJVTKEAESJXJYLFDSPVRFAJUXDINFAKLFQEFAEXJYNMTDXKSRQU"
        "GOVVTTWUHEXEZLGYVPEOLJHEMCOGEFLRIOSLBFRSRJGFKLEFWUAESLAYQIISVUVWKVZEZA"
        "FKVWPAFKXKSAOGMKKSRPWJHIHUXQSNKLODARXUAADJSGKMSEMWWSCARWVXIELVMVZVJODW"
        "PTDTLQESGPGOYEMGZGAFAGGJWEDNAVVWNAOWGTVYBLUXIXAUFUHDQUZAUTKMOZKTRUIFMM"
        "DMNMTTLZXBIYZWUXJWADQLHUICDQHMKLEOGEFLRIOSLBFRSEGDXCCIZLZXYENPKGYKLEQF"
        "VNJIRFZALRTPXAWLSSTTOZXEXHQVSMRMSUFEHKMOZGNXIILQULKFRIOFWMNSRWKGKRXRQK"
        "LHEENQDWVKVOZAUWVZIOWAYKLEOGEFLRIOSLBFRSBJGOZHEDAKLVVVQVOBKLAISJKRRTEW"
        "WDZRGFZGLVGOYEMGZGAFAGGJXHQHJHMMDQJUTEROFHJHMMDQLZXUETMTWVRYSQALARWDQK"
        "AZEIDFZWMVGHZGDHXCSGUZMYETULUTEROFTWTTGEEKWWSCAZQLAZVDBSJMPAEPGFHKLAHW"
        "SGPWIXNWKSYLXWLLRRDFZWWZWCGKKBFRSIALAZRTTWWQVGUFANXSVAZUZTIISFADEFRGAA"
        "FZNLIXWLAVVETSKGFXYQLTXVRAPWUBJMOZOZXKLEDLGLVIKXWYBJPAFAGGNIMGKLPFVKIA"
        "LATSNSJWLJMNPMKMICAOSVXDMCEHJBMECKYJHLTSMFVHKLEDKLHTVARLSGRTPDGSVYXHML"
        "SWUVEEKWLRPLAXLAVQUXLAICICAEHXKMNSUGGTIRZKLARXHMNWUVINFZWYFGUEGXLFQUOZ"
        "VXSETQTMMNICMFSECEGDWWMYETIWOBCPNQWVHEKOUFYAFREELSGUMNRGJFVHPGTDBTHENS"
        "LXRFOGLZHNFEELLHGVOFWUMCMBQJLRRRDEWUNIMTKAFUFXHAMJERASMFVHLVTQUZGFPOSQ"
        ;

    if (argument_count > 2)
    {
        std::cerr << "Usage: project2 [ciphertext-file]\n";
        return 1;
    }

    try
    {
        const std::string ciphertext = argument_count == 2
            ? project2::read_ciphertext(argument_values[1]) : embedded_ciphertext;
        print_report(ciphertext);
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
    return 0;
}
