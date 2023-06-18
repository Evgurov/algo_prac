// ID: 88320499
// =============================================================================
// Descripton:
// -----------------------------------------------------------------------------
// To find longest common prefix two steps should be performed.
// 1. Unpack recursively input strings.
// 2. Find longest common prefix of unpacked strings.
//    * Take first string as current longest common prefix. 
//    * Run through all strings and find common part with current longest 
//      prefix.
//
// Time complexity: 
// -----------------------------------------------------------------------------
// * Recursive unpacking of single string is O(n) in best case 
// (no recursive calls) and O(n^2 + k) with string like k1[k2[k3[...]]], 
// where n is a packed string length and k is unpacked string length. O(n^2) to
// read all symbols from packed string and O(k) to write into resulting string.
// Then unpacking of m strings will be O(m * n^2) in worst 
// case.
// * Finding longest common prefix of unpacked strings is O(m * k) in worst 
// case.
// Overall: O(n^2 + k + m * k)
//
// Memory complexity: 
// -----------------------------------------------------------------------------
// O(m * k) to store m unpacked strings.
// =============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool is_letter(const char c) {
    return (c >= 'a') && (c <= 'z');
}

bool is_digit(const char c) {
    return (c >= '0') && (c <= '9');
}

int str_to_int(const std::string& str) {
    std::istringstream string_stream (str);
    int res;
    string_stream >> res;

    return res;
}

std::string unpack(const std::string& str) {
    std::string unpacked_string;
    size_t iter = 0;
    while (iter < str.length()) {
        // if symbol is letter just add it to resulting string
        if (is_letter(str[iter])) {
            unpacked_string += str[iter];
            iter++;
        } 
        // if symbol is digit
        if (is_digit(str[iter])) {
            // form a number of repetitions from next few symbols
            std::string number = "";
            while (is_digit(str[iter])) {
                number += str[iter];
                iter++;
            }

            // form a substring in brackets after the number
            iter++; // skip '['
            std::string string_in_brackets = "";
            int count_brackets = 1;
            while (count_brackets != 0) {
                if (str[iter] == '[') {
                    count_brackets++;
                }
                if (str[iter] == ']') {
                    count_brackets--;
                }
                string_in_brackets += str[iter];
                iter++;
            }
            string_in_brackets.pop_back(); // pop last ']'

            // recursively unpack substring in brackets and add it to resulting
            // string required number of times
            string_in_brackets = unpack(string_in_brackets);
            for (int j = 0; j < str_to_int(number); ++j) {
                unpacked_string += string_in_brackets;
            }
        }
    }

    return unpacked_string;
}

std::string find_longest_common_prefix(std::vector<std::string>& strings) {
    std::string longest_common_prefix = strings[0];

    for (const auto& str : strings) {
        size_t iter = 0;
        while (str[iter] == longest_common_prefix[iter]) {
            iter++;
        }
        longest_common_prefix = longest_common_prefix.substr(0, iter);
    }

    return longest_common_prefix;
}

int main() {
    std::ifstream in; std::ofstream out;
    in.open("input.txt"); out.open("output.txt");


    int n;
    in >> n;
    std::vector<std::string> strings (n);
    for (auto& string : strings) {
        in >> string;
        string = unpack(string);
    }

    out << find_longest_common_prefix(strings);

    in.close(); out.close();
}