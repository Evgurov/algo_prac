#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> find_match(const std::vector<int>& vec, const std::vector<int>& temp) {
    std::vector<int> match_positions;
    for (int i = 0; i <= vec.size() - temp.size(); ++i) {
        bool match = true;
        int c = vec[i] - temp[0];
        for (int j = 1; j < temp.size(); ++j) {
            if (vec[i + j] != temp[j] + c) {
                match = false;
                break;
            }
        }
        if (match) {
            match_positions.push_back(i + 1);
        }
    }

    return match_positions;
}

int main() {
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int n, m;
    in >> n;
    std::vector<int> time_series (n);
    for (auto& measurement : time_series) {
        in >> measurement;
    }
    in >> m;
    std::vector<int> temp (m);
    for (auto& elem : temp) {
        in >> elem;
    }

    std::vector<int> match_positions = find_match(time_series, temp);
    for (auto& elem : match_positions) {
        out << elem << " ";
    }

    in.close();
    out.close();
}