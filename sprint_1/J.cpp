# include <iostream>
# include <fstream>
# include <vector>
# include <cmath>

std::vector<int> factorize(int N){
    std::vector<bool> sieve(sqrt(N), 0);
    std::vector<int> factorization;
    long long p;
    int i = 2;
    long long n = N;
    while(i * i <= n){
        p = i * i;
        while(p * p < n){
            sieve[p] = 1;
            p = p + i;
        }
        if (n % i == 0){
            while(n != 1 && n % i == 0){
                factorization.push_back(i);
                n = n / i;
            }
        }
        i = i + 1;
        while (sieve[i] == 1){
            i = i + 1;
        }
    }
    if (n != 1){
        factorization.push_back(n);
    }

    return factorization;
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

    print_vec(factorize(n), out);

    in.close();
    out.close();
}