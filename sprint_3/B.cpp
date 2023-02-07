#include <iostream>
#include <fstream>
#include <map>

std::map<int, std::string> keyboard {
    {'2', "abc"},
    {'3', "def"},
    {'4', "ghi"},
    {'5', "jkl"},
    {'6', "mno"},
    {'7', "pqrs"},
    {'8', "tuv"},
    {'9', "wxyz"},
};

void generate_combinations(std::ofstream &out, std::string &numbers, std::string prefix, int n){
    if (n == numbers.length()){
        out << prefix << " ";
    } else {
        for (int i = 0; i < keyboard[numbers[n]].length(); ++i){
            generate_combinations(out, numbers, prefix + keyboard[numbers[n]][i], n + 1);
        }
    }
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    std::string numbers;
    in >> numbers;

    generate_combinations(out, numbers, "", 0);

    in.close();
    out.close();
}