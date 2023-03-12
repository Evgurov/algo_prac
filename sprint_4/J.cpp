#include <iostream>
#include <fstream>

#include <set>
#include <unordered_map>

#include <vector>

#include <tuple>

#include <algorithm>

std::ifstream in;
std::ofstream out;

void print_fours(std::set<std::tuple<int, int, int, int>> fours) {
    out << fours.size() << std::endl;
    for (const auto& four : fours) {
        out << std::get<0>(four) << " ";
        out << std::get<1>(four) << " ";
        out << std::get<2>(four) << " ";
        out << std::get<3>(four) << std::endl;
    }
}

std::set<std::tuple<int, int, int, int>> four_sum(long S, std::vector<int>& arr) {
    std::unordered_map< long, std::vector<std::pair<int, int>> > history;
    std::set<std::tuple<int, int, int, int>> fours;
    long target;

    if (arr.size() == 0) {
        return fours;
    }

    std::sort(arr.begin(), arr.end());

    for (int i = 0; i < arr.size() - 1; ++i) {
        for(int j = i + 1; j < arr.size(); ++j) {
            target = S - arr[i] - arr[j];
            if (history.find(target) != history.end()) {
                for (const auto& pair : history[target]) {
                    if (pair.second < i) {
                        fours.insert(std::make_tuple(arr[pair.first], arr[pair.second], arr[i], arr[j]));
                    }
                }
            }
            history[arr[i] + arr[j]].push_back(std::make_pair(i, j));
        }
    }

    return fours;
}

int main() {
    in.open("input.txt");
    out.open("output.txt");

    long n, S;
    in >> n >> S;

    std::vector<int> arr (n);
    for (auto& elem : arr) {
        in >> elem;
    }

    print_fours(four_sum(S, arr));

    in.close();
    out.close();
}