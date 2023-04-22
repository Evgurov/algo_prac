// ID: 86220517
// =============================================================================
// Implemented algorithm for maximal spanning tree search is Prim's algorithm,
// based on priority queue. At the beginning there is starting vertex in a 
// queue. On each step algorithm takes the edge with the biggest weight from 
// the priority queue, marks incident vertex as processed and pushes all 
// non-processed neighbours of the vertex into the queue. If the taken vertex
// is already processed it does nothing.
// -----------------------------------------------------------------------------
// Time complexity: O(|E| log(|V|)
// Memory complexity: O(|V| + |E|)
// =============================================================================

#include <iostream>
#include <fstream>

#include <limits>

#include <vector>
#include <queue>

std::ifstream in;
std::ofstream out;

void fill_adjacency_list(
    std::istream& in, 
    std::vector<std::vector<std::pair<int, int>>>& adjacency_list, 
    int num_edges) {
// Function to fill the adjacency list of the graph, considers every edge as 
// unordered
// -----------------------------------------------------------------------------
// * `in` is an input stream to read a list of edges.
// * `adjacency_list` is an array of arrays of pairs:
//   - i-th element contains an erray of all vertices adjacent to the i-th 
//     vertex.
//   - each vertex in this array is represented as a pair (vertex number, 
//     weight of the edge incident to this vertex)
// * `num_edges` is number of edges to read.
// -----------------------------------------------------------------------------
    int u, v, weight;
    for (int i = 0; i < num_edges; ++i) {
        in >> u >> v >> weight;
        adjacency_list[u - 1].push_back(std::make_pair(v, weight));
        adjacency_list[v - 1].push_back(std::make_pair(u, weight));
    }
}

bool all_processed(const std::vector<bool>& processed) {
// Function which return whether all vertices are processed during the
// spanning_tree construction or not

    for (const auto& is_processed : processed) {
        if (!is_processed) {
            return false;
        }
    }

    return true;
}

int max_spanning_tree(
    const std::vector<std::vector<std::pair<int, int>>>& adjacency_list, 
    int start) {
// Max_spanning_tree construction
// -----------------------------------------------------------------------------
// * `adjacency_list` is an array of arrays of pairs:
//   - i-th element contains an erray of all vertices adjacent to the i-th
//   vertex.
//   - each vertex in this array is represented as a pair (vertex number, 
//     weight of the edge incident to this vertex)
// * `start` - starting vertex of the algorithm (can be any)
// -----------------------------------------------------------------------------
// Returns the weight of the maximal spanning tree or '-1' if there are several
// connected components in a graph.

    std::priority_queue<std::pair<int, int>> vertices_to_process;
    std::vector<bool> processed(adjacency_list.size(), false);

    int tree_weight = 0;

    vertices_to_process.push(std::make_pair(0, start));
    while (!vertices_to_process.empty()) {
        int new_vertex = vertices_to_process.top().second;
        int new_weight = vertices_to_process.top().first;
        vertices_to_process.pop();

        if (!processed[new_vertex - 1]) {
            tree_weight += new_weight;
            for (const auto& adj_vertex : adjacency_list[new_vertex - 1]) {
                if (processed[adj_vertex.first - 1] == false) {
                    vertices_to_process.push(std::make_pair(adj_vertex.second, adj_vertex.first));
                }
            }
            processed[new_vertex - 1] = true;
        }
    }

    if (!all_processed(processed)) {
        return -1;
    }

    return tree_weight;
}

int main() {
    in.open("input.txt");
    out.open("output.txt");

    int num_vertices, num_edges;
    in >> num_vertices >> num_edges;
    std::vector<std::vector<std::pair<int, int>>> adjacency_list (num_vertices);
    fill_adjacency_list(in, adjacency_list, num_edges);
    int tree_weight = max_spanning_tree(adjacency_list, 1);

    if (tree_weight == -1) {
        out << "Oops! I did it again";
    } else {
        out << tree_weight;
    }

    in.close();
    out.close();
}