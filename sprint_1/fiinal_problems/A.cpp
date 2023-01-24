//successful submition ID:81256899

#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> closest_zero(std::vector<int> &street){
    std::vector<int>::iterator iter;
    int count = -1;
    for (iter = street.begin(); iter != street.end(); ++iter){
        if (*iter == 0){
            count = 1;
        } else if (count == -1){
            *iter = count;
        } else {
            *iter = count;
            count++;
        }
    }
    for (iter = street.end() - 1; iter != street.begin() - 1; --iter){
        if (*iter == 0){
            count = 1;
        } else if (*iter > count){
            *iter = count;
            count++;
        } else if (*iter == -1){
            *iter = count;
            count++;
        }
    }
    return street;
}

void print_vec(std::vector<int> vec, std::ofstream &out){
    for(int i = 0; i < vec.size(); ++i){
        out << vec[i] << " ";
    }
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;

    std::vector<int> street(n);
    for (int i = 0; i < n; ++i){
        in >> street[i];
    }

    print_vec(closest_zero(street), out);

    in.close();
    out.close();
}