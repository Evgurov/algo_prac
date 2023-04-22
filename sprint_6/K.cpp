#include <iostream>
#include <fstream>

#include <limits>

#include <vector>
#include <set>
#include <queue>

std::ifstream in;
std::ofstream out;

void fill_adjacency_list(std::istream& in, std::vector<std::set<std::pair<int, int>>>& adjacency_list, int num_edges) {
    int u, v, weight;
    for (int i = 0; i < num_edges; ++i) {
        in >> u >> v >> weight;
        adjacency_list[u - 1].insert(std::make_pair(v, weight));
        adjacency_list[v - 1].insert(std::make_pair(u, weight));
    }
}

void relax(std::vector<int>& dist, int current, int previous, int weight) {
    if (dist[current - 1] > dist[previous - 1] + weight) {
        dist[current - 1] = dist[previous - 1] + weight;
    }
}

auto dijkstra(const std::vector<std::set<std::pair<int, int>>>& adjacency_list, int start) {
    std::vector<int> dist(adjacency_list.size(), std::numeric_limits<int>::max());
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> vertices_to_process;
    std::vector<bool> visited(adjacency_list.size(), false);

    vertices_to_process.push(std::make_pair(0, start));
    dist[start - 1] = 0;
    while (!vertices_to_process.empty()) {
        int cur_vertex = vertices_to_process.top().second;
        if (visited[cur_vertex - 1] == false) {
            for (auto adj_vertex : adjacency_list[cur_vertex - 1]) {
                if (visited[adj_vertex.first - 1] == false) {
                    relax(dist, adj_vertex.first, cur_vertex, adj_vertex.second);
                    vertices_to_process.push(std::make_pair(dist[adj_vertex.first - 1], adj_vertex.first));
                }
            }
            visited[cur_vertex - 1] = true;
        }
        vertices_to_process.pop();
    }

    return dist;
}

int main() {
    in.open("input.txt");
    out.open("output.txt");

    int num_vertices, num_edges;
    in >> num_vertices >> num_edges;
    std::vector<std::set<std::pair<int, int>>> adjacency_list (num_vertices);
    fill_adjacency_list(in, adjacency_list, num_edges);

    std::vector<std::vector<int>> dist_matrix (num_vertices, std::vector<int> (num_vertices));
    for (int start = 1; start <= num_vertices; ++start) {
        dist_matrix[start - 1] = dijkstra(adjacency_list, start);
    }

    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0;  j < num_vertices; ++j) {
            if (dist_matrix[i][j] != std::numeric_limits<int>::max()) {
                out << dist_matrix[i][j] << " ";
            } else {
                out << "-1" << " ";
            }
        }
        out << std::endl;
    }

    in.close();
    out.close();
}