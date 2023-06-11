// ID: 88127956	
// =============================================================================
// * In `dp[i][j]` the boolean value is stored. `true` if there is a subset of 
//   set of first j elements, sum of elements of which is equal to i. `dp` is of
//   size (m/2)x(n), where m - sum of all elements if input array, n - size
//   of input array.
// * Base case:
//   For array of size 0, there are no subsets with sum >= 0 then dp[:][0] =
//   false. There are no subsets with sum 0 in any set of positive numbers so
//   dp[0][:] = false. In array of length 1, there is a subset with sum k, if
//   k = arr[0].
// * Transition:
//   dp[i][j] = dp[i][j-1] or dp[i-arr[j]][j-1].
//   In array of size j there is a subset with sum i if in subset of size j-1
//   there is a subset with sum i, or if in subset of size j-1 there is a subset
//   with sum i - arr[j].
// * Items in `dp` can be calculated row-wise or column-wise
// * In dp[m/2][n] - right-down corner there is an answer if there is a
//   subset with sum equal to m/2. If dp[m/2][n] is true and m is even then the 
//   final answer is true. Otherwise false.
// -----------------------------------------------------------------------------
// Time complexity: O(m*n), where m is the sum of all elements in input array, 
// n is the size of input array.
// Memory complexity: O(m*n)
// =============================================================================

#include <iostream>
#include <fstream>
#include <vector>

bool is_equal(const std::vector<int>& arr) {
    int sum = 0;
    for (const auto& elem : arr) {
        sum += elem;
    }
    if (sum % 2) {
        return false;
    }

    std::vector<std::vector<bool>> dp (sum / 2 + 1, std::vector<bool> (arr.size() + 1));
    for (int i = 1; i <= sum / 2; ++i) {
        dp[i][1] = (arr[0] == i);
    }
    for (int j = 2; j <= arr.size(); ++j) {
        for (int i = 1; i <= sum / 2; ++i) {
            if (i >= arr[j-1]) {
                dp[i][j] = (dp[i][j-1] || dp[i - arr[j-1]][j-1]);
            } else {
                dp[i][j] = dp[i][j-1];
            }
        }
    }

    return dp[sum/2][arr.size()];
}

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;
    std::vector<int> arr (n);
    for (auto& elem : arr) {
        in >> elem;
    }

    if (is_equal(arr)) {
        out << "True"; 
    } else {
        out << "False";
    }

    in.close();
    out.close();
}