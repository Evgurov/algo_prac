#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> two_sum_naive(const std::vector<int> &arr, int k){
    int n = arr.size();
    std::vector<int> target_elems;
    for (int i = 0; i < n; ++i){
        for (int j = i + 1; j < n; ++j){
            if (arr[i] + arr[j] == k){
                target_elems.push_back(arr[i]);
                target_elems.push_back(arr[j]);
                return target_elems;
            }
        }
    }
    return target_elems;
}

void print_vec(std::vector<int> target_elems, std::ofstream &out){
    if (target_elems.size() != 2){
        out << "None";
    } else {
        out << target_elems[0] << " " << target_elems[1];
    }
}

int main(){
    std::ifstream in;
    std::ofstream out;

    in.open("input.txt");
    out.open("output.txt");
    
    int n, k;
    in >> n;

    std::vector<int> elems(n);

    for (int i = 0; i < n; ++i){
        in >> elems[i];
    }

    in >> k;

    print_vec(two_sum_naive(elems, k), out);

    in.close();
    out.close();
    return 0;
}