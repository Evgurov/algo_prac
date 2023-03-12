#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

std::ifstream in;
std::ofstream out;

bool fill_table(std::string& str_first, std::string& str_second) {
    std::unordered_map<char, char> table;
    for (int position = 0; position < str_first.length(); ++position) {
        if (table.find(str_first[position]) != table.end()) {
            if (table[str_first[position]] != str_second[position]) {
                return false;
            }
        } else {
            table[str_first[position]] = str_second[position];
        }
    }

    return true;
}

int main() {
    in.open("input.txt"); out.open("output.txt");

    std::string first_str, second_str;
    in >> first_str >> second_str;

    if (first_str.length() != second_str.length()) {
        out << "NO";
        in.close(); out.close();
        return 0;
    }

    if (fill_table(first_str, second_str) && fill_table(second_str, first_str)) {
        out << "YES";
    } else {
        out << "NO";
    }

    in.close(); out.close();
    return 0;
}