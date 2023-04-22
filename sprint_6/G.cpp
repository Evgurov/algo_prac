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

template <class VertexType, class DistanceType = unsigned>
auto BFS_with_distances(std::unordered_map<VertexType, std::set<VertexType>>& adjacency_list, VertexType start) {
    std::queue<VertexType> call_queue;
    std::unordered_set<VertexType> visited_vertices;

    std::unordered_map<VertexType, DistanceType> distances; 

    distances[start] = 0;
    call_queue.push(start);
    visited_vertices.insert(start);
    while (!call_queue.empty()) {
        VertexType cur_vertex = call_queue.front();
        for (auto& adjacent_vertex : adjacency_list[cur_vertex]) {
            if (visited_vertices.find(adjacent_vertex) == visited_vertices.end()) {
                call_queue.push(adjacent_vertex);
                visited_vertices.insert(adjacent_vertex);
                distances[adjacent_vertex] = distances[cur_vertex] + 1;
            }
        }
        call_queue.pop();
    }

    return distances;
}

int main() {
    in.open("input.txt");
    out.open("output.txt");

    int num_vertices, num_edges;
    in >> num_vertices >> num_edges;

    std::unordered_map<int, std::set<int>> adjacency_list = get_unordered_adgacency_list<int>(in, num_edges);

    int start;
    in >> start;

    auto distances = BFS_with_distances(adjacency_list, start);

    int max_dist = 0;
    for (const auto& vertex_distance_pair : distances) {
        if (vertex_distance_pair.second > max_dist) {
            max_dist = vertex_distance_pair.second;
        }
    }

    out << max_dist;

    in.close();
    out.close();
}