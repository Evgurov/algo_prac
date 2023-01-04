# include <iostream>
# include <fstream>

bool is_power_of_four(int n){
    bool result = true;
    while (n != 1){
        if (n % 4 != 0){
            result = false;
            break;
        } else {
            n /= 4;
        }
    }

    return result;
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;

    if (is_power_of_four(n)){
        out << "True";
    } else {
        out << "False";
    }

    in.close();
    out.close();
}