#include <iostream>
#include <fstream>

#include <vector>

#include <unordered_map>

#include <set>
#include <unordered_set>

#include <stack>

std::ifstream in;
std::ofstream out;

enum Color {white, grey, black};

template<class VertexType>
auto get_adjacency_list(std::istream& in, int num_edges) {
    std::unordered_map<VertexType, std::set<VertexType>> adjacency_list;
    VertexType v, u;
    for (int i = 0 ; i < num_edges; ++i) {
        in >> u >> v;
        adjacency_list[u].insert(v);
    }

    return adjacency_list;
}

template <class VertexType>
auto TopologySort(std::unordered_map<VertexType, std::set<VertexType>>& adjacency_list) {
    std::stack<VertexType> reversed_sorted;
    std::unordered_map<VertexType, Color> vertex_colors;
    for (const auto& vertex : adjacency_list) {
        DFS(adjacency_list, reversed_sorted, vertex_colors, vertex.first);
    }

    return reversed_sorted;
}


template <class VertexType>
void DFS(std::unordered_map<VertexType, std::set<VertexType>>& adjacency_list,
         std::stack<VertexType>& reversed_sorted,
         std::unordered_map<VertexType, Color>& vertex_colors,
         VertexType start) {

    std::stack<VertexType> callstack;

    callstack.push(start);
    while (!callstack.empty()) {
        VertexType cur_vertex = callstack.top();
        if (vertex_colors[cur_vertex] == black) {
            callstack.pop();
        }
        if (vertex_colors[cur_vertex] == grey) {
            callstack.pop();
            vertex_colors[cur_vertex] = black;
            reversed_sorted.push(cur_vertex);
        }
        if (vertex_colors[cur_vertex] == white) {
            vertex_colors[cur_vertex] = grey;
            for (auto iter = adjacency_list[cur_vertex].rbegin(); iter != adjacency_list[cur_vertex].rend(); iter++) {
                if (vertex_colors[*iter] != grey && vertex_colors[*iter] != black) {
                    callstack.push(*iter);
                }
            }
        }
    }
}

int main() {
    in.open("input.txt");
    out.open("output.txt");

    int num_vertices, num_edges;
    in >> num_vertices >> num_edges;

    auto adjacency_list = get_adjacency_list<int>(in, num_edges);
    for (int i = 1; i <= num_vertices; ++i) {
        if (adjacency_list.find(i) == adjacency_list.end()) {
            std::pair<int, std::set<int>> new_pair;
            new_pair.first = i;
            adjacency_list.insert(new_pair);
        }
    }

    auto reversed_sorted = TopologySort(adjacency_list);

    while (!reversed_sorted.empty()) {
        out << reversed_sorted.top() << " ";
        reversed_sorted.pop();
    }

    in.close();
    out.close();
}