#include <iostream>
#include <fstream>
#include <unordered_map>

std::string insert_strings(
    const std::string& str, 
    std::unordered_map<int, std::string> strings) {
        
    std::string new_str;
    int i;
    for (i = 0; i < str.length(); ++i) {
        if (strings.find(i) != strings.end()) {
            new_str += strings[i];
        }
        new_str += str[i];
    }

    if (strings.find(i) != strings.end()) {
        new_str += strings[i];
    }

    return new_str;
}

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    std::string initial_string;
    in >> initial_string;

    int n;
    in >> n;
    std::unordered_map<int, std::string> strings_to_insert;
    for (int i = 0; i < n; ++i) {
        std::string new_str; int k;
        in >> new_str >> k;
        strings_to_insert[k] = new_str;
    }

    out << insert_strings(initial_string, strings_to_insert);

    in.close();
    out.close();
}