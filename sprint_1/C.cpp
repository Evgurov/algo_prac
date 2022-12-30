#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> find_neighbours(std::vector<std::vector<int>> &mat, int n, int m, int x, int y){
    std::vector<int> neighbours;
    if (n == 1){
        if (m == 1){
            return neighbours;
        } else {
            if (x == 0){
                neighbours.push_back(mat[y][x+1]);
            } else if (x == m-1){
                neighbours.push_back(mat[y][x-1]);
            } else {
                neighbours.push_back(mat[y][x-1]);
                neighbours.push_back(mat[y][x+1]);
            }
            return neighbours;
        }
    } else if (m == 1){
        if (y == 0){
            neighbours.push_back(mat[y+1][x]);
        } else if (y == n - 1){
            neighbours.push_back(mat[y-1][x]);
        } else {
            neighbours.push_back(mat[y-1][x]);
            neighbours.push_back(mat[y+1][x]);
        }
        return neighbours;
    } else {
        if (y == 0){
            if (x == 0){
                neighbours.push_back(mat[y][x+1]);
                neighbours.push_back(mat[y+1][x]);
            } else if (x == m - 1){
                neighbours.push_back(mat[y][x-1]);
                neighbours.push_back(mat[y+1][x]);
            } else {
                neighbours.push_back(mat[y][x-1]);
                neighbours.push_back(mat[y+1][x]);
                neighbours.push_back(mat[y][x + 1]);
            }
        } else if (y == n - 1){
            if (x == 0){
                neighbours.push_back(mat[y - 1][x]);
                neighbours.push_back(mat[y][x + 1]);
            } else if (x == m - 1){
                neighbours.push_back(mat[y][x - 1]);
                neighbours.push_back(mat[y - 1][x]);
            } else {
                neighbours.push_back(mat[y][x-1]);
                neighbours.push_back(mat[y-1][x]);
                neighbours.push_back(mat[y][x+1]);
            }
        } else if (x == 0){
            neighbours.push_back(mat[y-1][x]);
            neighbours.push_back(mat[y][x+1]);
            neighbours.push_back(mat[y+1][x]);
        } else if (x == m - 1){
            neighbours.push_back(mat[y-1][x]);
            neighbours.push_back(mat[y+1][x]);
            neighbours.push_back(mat[y][x-1]);            
        } else {
            neighbours.push_back(mat[y-1][x]);
            neighbours.push_back(mat[y][x+1]);
            neighbours.push_back(mat[y+1][x]);
            neighbours.push_back(mat[y][x-1]);
        }
    }
    return neighbours;
}

std::vector<int> find_neighbours_pad(std::vector<std::vector<int>> &mat, int n, int m, int x, int y){
    std::vector<std::vector<int>> mat_padded (n + 2, std::vector<int> (m + 2, -1001));
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            mat_padded[i + 1][j + 1] = mat[i][j];
        }
    }

    std::vector<int> neighbours_aux;
    neighbours_aux.push_back(mat_padded[y][x+1]);
    neighbours_aux.push_back(mat_padded[y+1][x+2]);
    neighbours_aux.push_back(mat_padded[y+2][x+1]);
    neighbours_aux.push_back(mat_padded[y+1][x]);

    std::vector<int> neighbours;
    for (int i = 0; i < 4; ++i){
        if (neighbours_aux[i] != -1001){
            neighbours.push_back(neighbours_aux[i]);
        }
    }

    return neighbours;
}

void print_vec(std::vector<int> vec, std::ofstream &out){
    int length = vec.size();
    for (int i = 0; i < length - 1; ++i){
        for (int j = i; j < length; ++j){
            if (vec[i] > vec[j]){
                std::swap(vec[i], vec[j]);
            }
        }
    }
    for (int i = 0; i < length; ++i){
        out << vec[i] << " ";
    }
}

int main(){
    std::ifstream in;
    std::ofstream out;

    in.open("input.txt");
    out.open("output.txt");

    int n,m;
    in >> n >> m;

    std::vector<std::vector<int>> mat(n, std::vector<int> (m));

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < m; ++j){
            in >> mat[i][j];
        }
    }
    int x, y;
    in >> y >> x;

    print_vec(find_neighbours_pad(mat, n, m, x, y), out);

    in.close();
    out.close(); 
    return 0;
}