#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::ifstream in;
std::ofstream out;

void print_flowerbeds(const std::vector<std::vector<int>>& intervals_sorted){
    auto iter = intervals_sorted.cbegin();
    int begin = (*iter)[0];
    int end = (*iter)[1];
    iter++;
    while (iter != intervals_sorted.cend()) {
        if ((*iter)[0] > end) {
            out << begin << " " << end << std::endl;
            begin = (*iter)[0];
            end = (*iter)[1];
        } else if ((*iter)[1] > end) {
            end = (*iter)[1];
        }
        iter++;
    }
    out << begin << " " << end;
}

int main(){
    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;

    std::vector<std::vector<int>> intervals (n, std::vector<int>(2)); 

    for (int i = 0; i < n; ++i){
        in >> intervals[i][0] >> intervals[i][1];
    }

    std::sort(intervals.begin(), intervals.end());
    print_flowerbeds(intervals);

    in.close();
    out.close();
}