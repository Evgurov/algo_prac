#include <iostream>
#include <fstream>

std::string leave_odd(std::string& str) {
    std::string new_str;
    for (auto c : str) {
        if (!(c % 2)) {
            new_str += c;
        }
    }

    return new_str;
}

int compare(const std::string& str_1, const std::string& str_2) {
    if (str_1 < str_2) {
        return -1;
    } else if (str_1 == str_2) {
        return 0;
    }

    return 1;
}

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    std::string first_str, second_str;
    in >> first_str >> second_str;

    out << compare(leave_odd(first_str), leave_odd(second_str));   

    in.close();
    out.close();
}