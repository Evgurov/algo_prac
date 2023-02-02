#include <iostream>
#include <cmath>

int fib_iter_mod(int n, int k){
    int s, s1 = 1, s2 = 1;
    for (int i = 2; i <= n; ++i){
        s = s2;
        s2 = (s1 + s2) % int(pow(10, k));
        s1 = s;
    }
    return s2;
}

int main(){
    int n, k;
    std::cin >> n >> k;
    std::cout << fib_iter_mod(n,k);
}