#include <iostream>
#include <fstream>
#include <vector>

std::ifstream in;
std::ofstream out;

long mod_sum(long left, long right, long mod) {
    return ((left % mod) + (right % mod)) % mod;
}

long mod_mult(long left, long right, long mod) {
    return ((left % mod) * (right % mod)) % mod;
}

long mod_sub(long left, long right, long mod) {
    return left < right ? mod - (right - left) : left - right; 
}

int main() {
    in.open("input.txt");
    out.open("output.txt");

    long a, m;
    std::string str;

    in >> a >> m >> str;

    std::vector<long> hashes(str.length() + 1);
    std::vector<long> a_powers(str.length());
    hashes[0] = 0;
    long hash = 0;
    long power = 1;
    for (int i = 1; i <= str.length(); ++i) {
        hash = mod_mult(hash, a, m);
        hash = mod_sum(hash, str[i-1], m);
        power = mod_mult(power, a, m);
        hashes[i] = hash;
        a_powers[i-1] = power;
    }

    int num_intervals;
    in >> num_intervals;

    int left, right;
    long left_hash;
    for (int i = 0; i < num_intervals; ++i) {
        in >> left >> right;
        left_hash = hashes[left - 1];
        left_hash = mod_mult(left_hash, a_powers[right - left], m);
        hash = mod_sub(hashes[right], left_hash, m);
        out << hash << std::endl;
    }

    in.close();
    out.close();
}