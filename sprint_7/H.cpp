#include <iostream>
#include <fstream>
#include <vector>


int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int n,m;
    in >> n >> m;

    std::vector<std::vector<bool>> field (n, std::vector<bool> (m));

    char c;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            in >> c;
            field[i][j] = (c == '1');
        }
    }

    std::vector<std::vector<int>> dp (n + 1, std::vector<int> (m + 1));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]) + field[n - i][j - 1];
        }
    }

    out << dp[n][m];


    in.close();
    out.close();
}