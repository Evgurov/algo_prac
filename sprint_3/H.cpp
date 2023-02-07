#include <iostream>
#include <fstream>
#include <functional>
#include <vector>
#include <algorithm>

std::ifstream in;
std::ofstream out;

std::function<bool(const std::string&,const std::string&)> my_greater = [](const std::string &a, const std::string &b){
    int i = 0;
    while (i < std::min(a.length(), b.length()) && a[i] == b[i]){
        ++i;
    } 
    if (i == a.length() && i == b.length()){
        return false;
    } else if (i == a.length()){
        return my_greater(a, b.substr(i, b.length() - i));
    } else if (i == b.length()){
        return my_greater(a.substr(i, a.length() - i), b);
    } else {
        return a[i] > b[i];
    }
};

void print_arr(const std::vector<std::string> &arr){
    std::vector<std::string>::const_iterator iter;
    for (iter = arr.cbegin(); iter != arr.cend(); ++iter){
        out << *iter;
    }
}

int main(){
    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;

    std::vector<std::string> numbers(n);

    for (int i = 0; i < n; ++i){
        in >> numbers[i];
    }

    std::sort(numbers.begin(), numbers.end(), my_greater);
    print_arr(numbers);

    in.close();
    out.close();
}