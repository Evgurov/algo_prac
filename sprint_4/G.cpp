#include <iostream>
#include <fstream>
#include <unordered_map>

std::ifstream in;
std::ofstream out;

int main() {
    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;

    std::unordered_map<int, int> sum_positions {{0, 0}};

    int round, interval, max_interval = 0, cur_sum = 0;
    for (int cur_pos = 1; cur_pos <= n; ++cur_pos) {
        in >> round;
        if (round == 1) {
            cur_sum++;
        } else {
            cur_sum--;
        }
        if (sum_positions.find(cur_sum) != sum_positions.end()) {
            interval = cur_pos - sum_positions[cur_sum];
            if (interval > max_interval) {
                max_interval = interval;
            }
        } else {
            sum_positions[cur_sum] = cur_pos;
        }
    }

    out << max_interval;

    in.close();
    out.close();
}