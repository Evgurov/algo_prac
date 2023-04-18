#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

std::ifstream in;
std::ofstream out;

template<class Vertex>
std::unordered_map<Vertex, std::vector<Vertex>> 
get_adgacency_list(std::istream& in, int num_edges) {
    std::unordered_map<Vertex, std::vector<Vertex>> adjacency_list;
    Vertex v, u;
    for (int i = 0 ; i < num_edges; ++i) {
        in >> u >> v;
        adjacency_list[u].push_back(v);
    }

    return adjacency_list;
}

int main() {
    in.open("input.txt");
    out.open("output.txt");

    int num_vertices, num_edges;
    in >> num_vertices >> num_edges;

    std::unordered_map<int, std::vector<int>> adjacency_list;
    adjacency_list = get_adgacency_list<int>(in, num_edges);

    for (int vertex = 1; vertex <= num_vertices; ++vertex) {
        if (adjacency_list.find(vertex) != adjacency_list.end()) {
            out << adjacency_list[vertex].size() << " ";
            for (int adjacent_vertex : adjacency_list[vertex]) {
                out << adjacent_vertex << " ";
            }
        } else {
            out << '0';
        }
        out << std::endl;
    }

    in.close();
    out.close();
}