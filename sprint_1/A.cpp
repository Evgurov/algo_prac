#include <iostream>
#include <fstream>


int compute_fun(int a, int b, int c, int x){
    return a * x * x + b * x + c;
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int a, b, c, x;
    in >> a >> x >> b >> c;

    out << compute_fun(a, b, c, x);

    in.close();
    out.close();
    return 0;
}