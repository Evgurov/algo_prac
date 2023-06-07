#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int n, M;
    in >> n >> M;
    std::vector<int> W (n);
    for (auto& w : W) {
        in >> w;
    }

    std::vector<std::vector<int>> dp (n + 1, std::vector<int> (M + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (j - W[i-1] < 0) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = std::max(dp[i-1][j], W[i-1] + dp[i-1][j - W[i-1]]);
            }
        }
    }

    out << dp[n][M];

    in.close();
    out.close();
}