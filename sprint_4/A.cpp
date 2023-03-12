#include <iostream>
#include <fstream>

std::ifstream in;
std::ofstream out;

long mod_sum(long left, long right, long mod) {
    return ((left % mod) + (right % mod)) % mod;
}

long mod_mult(long left, long right, long mod) {
    return ((left % mod) * (right % mod)) % mod;
}

int main() {
    in.open("input.txt");
    out.open("output.txt");

    long a, m;
    in >> a >> m;
    std::string str;
    in >> str;
    long hash = 0;
    for (const char& sym : str) {
        hash = mod_mult(hash, a, m);
        hash = mod_sum(hash, sym, m);
    }

    out << hash;

    in.close();
    out.close();
}