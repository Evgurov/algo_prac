#include <iostream>
#include <fstream>
#include <vector>

std::vector<double> moving_average(const std::vector<int> &Q, int k){
    int n = Q.size();
    std::vector<double> average(n - k + 1);

    double sum = 0;
    for (int i = 0; i < k; ++i){
        sum += Q[i];
    }

    for (int i = 0; i < n - k + 1; ++i){
        average[i] = sum / k;
        sum -= Q[i];
        sum += Q[i + k];
    }

    return average;
}

void print_vec(const std::vector<double> vec, std::ofstream &out){
    for(int i = 0; i < vec.size(); ++i){
        out << vec[i] << " ";
    }
}

int main(){
    std::ifstream in;
    std::ofstream out;

    in.open("input.txt");
    out.open("output.txt");

    int n, k;

    in >> n;

    std::vector<int> Q(n);
    for (int i = 0; i < n; ++i){
        in >> Q[i];
    }
    in >> k;

    print_vec(moving_average(Q, k), out);

    in.close();
    out.close();
    return 0;
}