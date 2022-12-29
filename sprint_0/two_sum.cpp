#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <set>

std::vector<int> two_sum_pointers(std::vector<int> &arr, int k){
    int n = arr.size();
    std::vector<int> target_elems;
    std::vector<int>::iterator left = arr.begin();
    std::vector<int>::iterator right = arr.end() - 1;

    while (left != right){
        if (*left + *right == k){
            target_elems.push_back(*left);
            target_elems.push_back(*right);
            return target_elems;
        } else if (*left + *right < k){
            left++;
        } else {
            right--;
        }
    }
    return target_elems;
}

std::vector<int> two_sum_set(std::vector<int> &arr, int k){
    int n = arr.size();
    std::vector<int> target_elems;    
    std::set<int> unique_elems;
    for (int i = 0; i < n; ++i){
        if (unique_elems.find(k - arr[i]) != unique_elems.end()){
            target_elems.push_back(arr[i]);
            target_elems.push_back(*unique_elems.find(k - arr[i]));
            return target_elems;
        } else {
            unique_elems.insert(arr[i]);
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

    // print_vec(two_sum_pointers(elems, k), out);
    print_vec(two_sum_set(elems, k), out);

    in.close();
    out.close();
    return 0;
}