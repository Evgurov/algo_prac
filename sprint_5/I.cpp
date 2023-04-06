#include <iostream>
#include <fstream>
#include <vector>

std::ifstream in;
std::ofstream out;

int main() {
    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;

    std::vector<int> N(n + 1); 
    N[0] = 1; N[1] = 1;

    for (int i = 2; i < n + 1; ++i) {
        int sum_i = 0;
        for (int j = 0; j < i; ++j) {
            sum_i += N[j] * N[i - j - 1];
        }
        N[i] = sum_i;
    }

    out << N[n];

    in.close();
    out.close();
}