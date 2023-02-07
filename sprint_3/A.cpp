#include <iostream>
#include <fstream>
#include <string>

void generate_brackets(std::ofstream &out, std::string prefix, int open, int close){
    if (open == 0 && close == 0){
        out << prefix << std::endl;
    } else if (open == 0) {
        generate_brackets(out, prefix + ")", open, close - 1); 
    } else if (close == open) {
        generate_brackets(out, prefix + "(", open - 1, close);
    } else {
        generate_brackets(out, prefix + "(", open - 1, close);
        generate_brackets(out, prefix + ")", open, close - 1);
    }
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;

    generate_brackets(out, "", n, n);

    in.close();
    out.close();
}