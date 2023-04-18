#include <iostream>
#include <fstream>
#include <vector>

std::ifstream in;
std::ofstream out;

template<class Vertex>
std::vector<std::vector<Vertex>>
get_adgacency_matrix(std::istream& in, int num_vertices, int num_edges) {
    std::vector<std::vector<Vertex>> adjacency_matrix(num_vertices, std::vector<Vertex>(num_vertices, 0));
    Vertex v, u;
    for (int i = 0 ; i < num_edges; ++i) {
        in >> u >> v;
        adjacency_matrix[u - 1][v - 1] = 1;
    }

    return adjacency_matrix;
}

int main() {
    in.open("input.txt");
    out.open("output.txt");

    int num_vertices, num_edges;
    in >> num_vertices >> num_edges;

    std::vector<std::vector<int>> adjacency_matrix = get_adgacency_matrix<int>(in, num_vertices, num_edges);

    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0; j < num_vertices; ++j) {
            out << adjacency_matrix[i][j] << " ";
        }
        out << std::endl;
    }

    in.close();
    out.close();
}