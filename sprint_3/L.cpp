#include <iostream>
#include <fstream>
#include <vector>

int mod_binsearch(std::vector<int> &arr, int left, int right, int value){
    if (left == right){
        if (arr[left] < value){
            return -1;
        } else {
            return left + 1;
        }
    } else if (arr[(left + right) / 2 ] >= value){
        return mod_binsearch(arr, left, (left+right) / 2, value);
    } else {
        return mod_binsearch(arr, (left+right) / 2 + 1, right, value);
    }
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;

    std::vector<int> arr (n);
    for (int i = 0; i < n; ++i){
        in >> arr[i];
    }

    int cost;
    in >> cost;

    out << mod_binsearch(arr, 0, n-1, cost) << " " <<  mod_binsearch(arr, 0, n-1, 2 * cost);

    in.close();
    out.close();
}