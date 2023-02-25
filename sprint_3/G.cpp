#include <iostream>
#include <fstream>
#include <vector>
#include <map>

std::ifstream in;
std::ofstream out;

void count_sort(std::vector<int>::iterator begin, std::vector<int>::iterator end){
    std::vector<int> count(3, 0);
    for (auto iter = begin; iter != end; iter++){
        ++count[*iter];
    }
    auto iter = begin;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < count[i]; ++j){
            *iter = i;
            iter++;
        }
    }
}

void print_vec(const std::vector<int>& vec){
    for (const auto& elem : vec){
        out << elem << " ";
    }
}


int main(){
    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;

    std::vector<int> arr (n);

    for (auto iter = arr.begin(); iter != arr.end(); ++iter){
        in >> *iter;
    }

    count_sort(arr.begin(), arr.end());
    print_vec(arr);

    in.close();
    out.close();
}