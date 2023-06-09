#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int first_seq_length;
    in >> first_seq_length;
    std::vector<int> first_seq (first_seq_length);
    for (auto& elem : first_seq) {
        in >> elem;
    }

    int second_seq_length;
    in >> second_seq_length;
    std::vector<int> second_seq (second_seq_length);
    for (auto& elem : second_seq) {
        in >> elem;
    }

    std::vector<std::vector<int>> dp (first_seq_length + 1, std::vector<int> (second_seq_length + 1));
    int i, j;
    for (i = 1; i <= first_seq_length; ++i) {
        for (j = 1; j <= second_seq_length; ++j) {
            if (first_seq[i-1] == second_seq[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }

    std::vector<int> first_longest_common_seq_idx;
    std::vector<int> second_longest_common_seq_idx;
    i--;
    j--;
    while (i != 0 && j != 0) {
        if (first_seq[i-1] == second_seq[j-1]) {
            first_longest_common_seq_idx.push_back(i);
            second_longest_common_seq_idx.push_back(j);
            j--; i--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }

    out << dp[first_seq_length][second_seq_length] << std::endl;
    for (auto iter = first_longest_common_seq_idx.rbegin(); iter != first_longest_common_seq_idx.rend(); iter++) {
        out << *iter << " ";
    }
    out << std::endl;
    for (auto iter = second_longest_common_seq_idx.rbegin(); iter != second_longest_common_seq_idx.rend(); iter++) {
        out << *iter << " ";
    }

    in.close();
    out.close();
}