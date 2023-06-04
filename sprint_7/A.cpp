#include <iostream>
#include <fstream>
#include <vector>


int count_income(const std::vector<int>& costs) {
    int max_income = 0;
    for (int i = 1; i < costs.size(); ++i) {
        if (costs[i - 1] < costs[i]) {
            max_income += costs[i] - costs[i-1]; 
        }
    }

    return max_income;
}

int main(){
    std::ifstream in;
    std::ofstream out;

    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;
    std::vector<int> costs(n);
    for (auto& cost : costs) {
        in >> cost;
    }

    out << count_income(costs);

    in.close();
    out.close();
}