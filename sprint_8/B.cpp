#include <iostream>
#include <fstream>

bool is_equal(const std::string& first_str, const std::string& second_str) {
    int l_first = first_str.length(); 
    int l_second = second_str.length();

    if (std::abs(l_first - l_second) > 1) {
        return false;
    }

    int length_equal = false;
    std::string str_1, str_2;
    if (l_first > l_second) {
        str_1 = first_str;
        str_2 = second_str;
    } else if (l_first == l_second) {
        length_equal = true;
        str_1 = first_str;
        str_2 = second_str;
    } else {
        str_1 = second_str;
        str_2 = first_str;
    }

    int iter_1 = 0, iter_2 = 0;
    int mismatch_count = 0;
    while (iter_1 < str_1.length()) {
        if (str_1[iter_1] != str_2[iter_2]) {
            mismatch_count++;
            if (mismatch_count > 1) {
                return false;
            }
            if (length_equal) {
                iter_1++; iter_2++;
            } else {
                iter_1++;
            }
        } else {
            iter_1++; iter_2++;
        }
    }

    return true;
}

int main() {
    std::ifstream in; std::ofstream out;
    in.open("input.txt"); out.open("output.txt");

    std::string first_str, second_str;
    in >> first_str >> second_str;

    if (is_equal(first_str, second_str)) {
        out << "OK";
    } else {
        out << "FAIL";
    }

    in.close(); out.close();
}