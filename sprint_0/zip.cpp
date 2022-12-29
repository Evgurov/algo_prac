#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> zip(const std::vector<int> &a, const std::vector<int> &b){
    int n = a.size();
    std::vector<int> zipped(2 * n);

    for (int i = 0; i < n; ++i){
        zipped[i * 2] = a[i];
        zipped[i * 2 + 1] = b[i];
    }

    return zipped;
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
    std::vector<int> a(n), b(n);

    for (int i = 0; i < n; ++i){
        in >> a[i];
    }

    for (int i = 0; i < n; ++i){
        in >> b[i];
    }

    print_vec(zip(a,b), out);

    in.close();
    out.close();

    return 0;
}