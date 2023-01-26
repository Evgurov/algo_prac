#include <iostream>
#include <fstream> 
#include <vector>

std::vector<std::vector<int>> transpose(const std::vector<std::vector<int>> &mat){
    int n = mat.size();
    int m = mat[0].size();
    std::vector<std::vector<int>> transposed_mat(m, std::vector<int> (n));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            transposed_mat[j][i] = mat[i][j];
        }
    }
    return transposed_mat;
}

void print_mat(const std::vector<std::vector<int>> &mat, std::ofstream &out){
    int n = mat.size(), m = mat[0].size();
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            out << mat[i][j] << " ";
        }
        out << '\n';
    }
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int m, n;
    in >> n >> m;

    if (n != 0 && m != 0){
        std::vector<std::vector<int>> mat(n, std::vector<int>(m));

        for (int i  = 0; i < n; ++i){
            for (int j = 0; j < m; ++j){
                in >> mat[i][j];
            }
        }

        print_mat(transpose(mat), out);
    }

    in.close();
    out.close();
}