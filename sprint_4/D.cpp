#include <iostream>
#include <fstream>
#include <unordered_set>

std::ifstream in;
std::ofstream out;

template <typename Type>
void print(const Type& container) {
    for (const auto& element : container) {
        out << element << std::endl;
    }
}

int main() {
    in.open("input.txt");
    out.open("output.txt");

    std::unordered_set<std::string> classes;

    int n;
    in >> n;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string class_name;

    for (int i = 0; i < n; ++i) {
        std::getline(in, class_name);
        if (classes.insert(class_name).second) {
            out << class_name << std::endl;
        }
    }

    in.close();
    out.close();
}