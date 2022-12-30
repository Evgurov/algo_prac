#include <iostream>
#include <fstream>

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int a, b, c;
    in >> a >> b >> c;

    int mist = c % 2;

    int evanness = (a % 2)*(a % 2);
    bool win = false;
    if ((b % 2)*(b % 2) == evanness){
        if ((c % 2)*(c % 2) == evanness){
            win = true;
        }
    }
    if(win){
        out << "WIN";
    } else {
        out <<"FAIL";
    }

    in.close();
    out.close();
    return 0;
}