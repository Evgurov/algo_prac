// ID: 88081263
// =============================================================================
// * In `dp[i][j]` levenshtein distance between prefixes of length i and j of 
//   string is stored.
// * Base case:
//   Levenshtein distance between strings of lengths 0 and n is n, where n >= 0
// * Transition:
//   dp[i][j] = min(dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1] + ...
//   + not_equal(s1[i], s2[j])), where not_equal(a,b) = 1, if a != b and 0, if 
//   a = b.
//   - dp[i-1][j] + 1 corresponds to adding one symbol to s1,
//   - dp[i][j-1] + 1 corresponds to adding one symbol to s2,
//   - dp[i-1][j-1] + not_equal(s1[i], s2[j]) corresponds to changing one symbol
//     in s1 or s2 (If symbols are same do not change)
// * Items in `dp` can be calculated row-wise or column-wise
// * Answer is in dp[n][m] - right-down corner.
// -----------------------------------------------------------------------------
// Time complexity: O(m*n), where m,n - sizes of input strings.
// Memory complexity: O(m*n)
// =============================================================================

#include <iostream>
#include <fstream>
#include <vector>

template <class Type>
const Type& min(const Type& a, const Type& b, const Type& c) {
    return std::min(std::min(a, b), c);
}

int count_levenshtein(const std::string& first, const std::string& second) {
    std::vector<std::vector<int>> dp (first.length() + 1, std::vector<int> (second.length() + 1));
    for (int i = 1; i <= first.length(); ++i) {
        dp[i][0] = i;
    }
    for (int j = 1; j <= second.length(); ++j) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= first.length(); ++i) {
        for (int j = 1; j <= second.length(); ++j) {
            dp[i][j] = min(dp[i-1][j] + 1, dp[i][j-1] + 1, dp[i-1][j-1] + (first[i-1] != second[j-1]));
        }
    }

    return dp[first.length()][second.length()];
}

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    std::string first_str, second_str;
    in >> first_str >> second_str;

    out << count_levenshtein(first_str, second_str);

    in.close();
    out.close();
}