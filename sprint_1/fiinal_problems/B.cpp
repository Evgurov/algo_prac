//successful submition ID:81268203

#include <iostream>
#include <fstream> 
#include <vector>

int find_digit(std::vector<std::vector<int>> &mat, int digit){
    int digits_found = 0;
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            if (mat[i][j] == digit){
                digits_found++;
            }
        }
    }
    return digits_found;
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int k;
    in >> k;

    std::vector<std::vector<int>> mat(4, std::vector<int> (4));
    
    char sym;
    in.get(sym);
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            in.get(sym);
            mat[i][j] = sym - '0';
        }
        in.get(sym);
    }

    int points = 0, digits_found;
    for (int digit = 1; digit <= 9; ++digit){
        digits_found = find_digit(mat, digit);
        if (digits_found > 0 && digits_found <= 2 * k){
            points++;
        }
    }

    out << points;

    in.close();
    out.close();
}