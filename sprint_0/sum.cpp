#include <iostream>
#include <fstream>

int sum(int a, int b){
    return a + b;
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int a, b, ab_sum;
    in >> a >> b;
    ab_sum = sum(a,b);
    out << ab_sum;

    in.close();
    out.close();
    
    return 0;
}