#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> prefix_fun(const std::string& str) {
    std::vector<int> pref_fun_values (str.length());

    for (int i = 1; i < str.length(); ++i) {
        int k = pref_fun_values[i-1];
        while (k != 0) {
            if (str[i] == str[k]) {
                pref_fun_values[i] = k + 1;
                break;
            } else {
                k = pref_fun_values[k-1];
            }
        }

        if ((k == 0) && (str[i] == str[k])) {
            pref_fun_values[i] = 1;
        }
    }

    return pref_fun_values;
}

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    std::string str;
    in >> str;

    std::vector<int> prefix_fun_values = prefix_fun(str);
    for (const auto& elem : prefix_fun_values) {
        out << elem << " ";
    }

    in.close();
    out.close();
}