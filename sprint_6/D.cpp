#include <iostream>
#include <fstream>

#include <set>
#include <unordered_set>

#include <unordered_map>

#include <queue>

std::ifstream in;
std::ofstream out;

template<class VertexType>
auto get_unordered_adgacency_list(std::istream& in, int num_edges) {
    std::unordered_map<VertexType, std::set<VertexType>> adjacency_list;
    VertexType v, u;
    for (int i = 0 ; i < num_edges; ++i) {
        in >> u >> v;
        adjacency_list[u].insert(v);
        adjacency_list[v].insert(u);
    }

    return adjacency_list;
}

template <class VertexType>
void BFS(std::unordered_map<VertexType, std::set<VertexType>>& adjacency_list, VertexType start) {
    std::queue<VertexType> call_queue;
    std::unordered_set<VertexType> visited_vertices;

    call_queue.push(start);
    while (!call_queue.empty()) {
        VertexType cur_vertex = call_queue.front();
        if (visited_vertices.find(cur_vertex) != visited_vertices.end()) {
            call_queue.pop();
        } else {
            visited_vertices.insert(cur_vertex);
            out << cur_vertex << " ";
            for (auto& adjacent_vertex : adjacency_list[cur_vertex]) {
                call_queue.push(adjacent_vertex);
            }
        }
    }
}

int main() {
    in.open("input.txt");
    out.open("output.txt");

    int num_vertices, num_edges;
    in >> num_vertices >> num_edges;

    std::unordered_map<int, std::set<int>> adjacency_list = get_unordered_adgacency_list<int>(in, num_edges);

    int start;
    in >> start;

    BFS(adjacency_list, start);

    in.close();
    out.close();
}