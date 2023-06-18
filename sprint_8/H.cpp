#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>

std::unordered_set<int> find_matches_places(
    const std::string& str, 
    const std::string& temp) {

    std::unordered_set<int> matches_places;

    std::vector<int> prefix_fun (temp.length());
    int prev_fun = 0;
    for (int i = 1; i < str.length(); ++i) {
        int k = prev_fun;
        while (k != 0) {
            if (str[i] == str[k]) {
                if (i < temp.length()) {
                    prefix_fun[i] = k + 1;
                }
                if (k + 1 == temp.length()) {
                    matches_places.insert(i - 2 * temp.length());
                }
                prev_fun = k + 1;
                break;
            } else {
                k = prefix_fun[k-1];
            }
        }

        if (k == 0){
            if (str[i] == str[k]) {
                if (i < temp.length()) {
                    prefix_fun[i] = 1;
                }
                if (temp.length() == 1) {
                    matches_places.insert(i - 2);
                }
                prev_fun = 1;
            } else {
                prev_fun = 0;
            }
        }
    }

    return matches_places;
}

std::string replace_substring(
    const std::string& text, 
    const std::string& substring, 
    const std::string& new_string) {

    std::string merged_text = substring + '#' + text;
    std::unordered_set<int> places_to_insert = find_matches_places(merged_text, substring);

    std::string result;
    for (int i = 0; i < text.length(); ++i) {
        if (places_to_insert.find(i) != places_to_insert.end()) {
            result += new_string;
            i += substring.length() - 1;
        } else {
            result += text[i];
        }
    }

    return result;
}

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    std::string text, substring, new_string;
    in >> text >> substring >> new_string;

    out << replace_substring(text, substring, new_string);

    in.close();
    out.close();
}