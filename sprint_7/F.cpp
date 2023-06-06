#include <iostream>
#include <fstream>
#include <vector>

int sum(const int a, const int b) {
    return (a + b) % 1000000007; 
}

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int n, k;
    in >> n >> k;

    std::vector<int> stairs (n + 1);
    stairs[1] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            if (i + j > n) {
                break;
            }

            stairs[i + j] = sum(stairs[i + j], stairs[i]);
        }
    }

    out << stairs[n];

    in.close();
    out.close();
}