#include <iostream>
#include <fstream>

#include <set>
#include <unordered_set>

#include <map>
#include <unordered_map>

#include <stack>

std::ifstream in;
std::ofstream out;

enum Color {white, grey, black};

template<class VertexType>
void get_unordered_adjacency_list(std::unordered_map<VertexType, std::set<VertexType>>& adjacency_list,
                                  std::istream& in,
                                  int num_edges) {
    VertexType v, u;
    for (int i = 0 ; i < num_edges; ++i) {
        in >> u >> v;
        adjacency_list[u].insert(v);
        adjacency_list[v].insert(u);
    }
}

template <class VertexType>
void DFS(std::unordered_map<VertexType, std::set<VertexType>>& adjacency_list,
         std::unordered_map<VertexType, int>& vertex_colors,
         int component_color,
         VertexType start) {

    std::stack<VertexType> callstack;

    callstack.push(start);
    while (!callstack.empty()) {
        VertexType cur_vertex = callstack.top();

        if (vertex_colors[cur_vertex] == 0) {
            callstack.pop();
            vertex_colors[cur_vertex] = component_color;
        } else if (vertex_colors[cur_vertex] == -1) {
            vertex_colors[cur_vertex] = 0;
            for (auto iter = adjacency_list[cur_vertex].rbegin(); iter != adjacency_list[cur_vertex].rend(); iter++) {
                if (vertex_colors[*iter] == -1) {
                    callstack.push(*iter);
                }
            }
        } else {
            callstack.pop();
        }
    }
}

template <class VertexType>
auto get_connected_components(std::unordered_map<VertexType, std::set<VertexType>>& adjacency_list) {
    std::unordered_map<VertexType, int> vertex_colors;
    for (const auto& vertex : adjacency_list) {
        vertex_colors[vertex.first] = -1;
    }

    int component_color = 1;
    for (auto& vertex : adjacency_list) {
        DFS(adjacency_list, vertex_colors, component_color, vertex.first);
        component_color++;
    }

    std::unordered_map<int, std::set<VertexType>> connected_components;
    for (auto& vertex_color_pair : vertex_colors) {
        connected_components[vertex_color_pair.second].insert(vertex_color_pair.first);
    }

    return connected_components;
}

int main() {
    in.open("input.txt");
    out.open("output.txt");

    int num_vertices, num_edges;
    in >> num_vertices >> num_edges;

    std::unordered_map<int, std::set<int>> adjacency_list;
    for (int i = 1; i <= num_vertices; ++i) {
        std::pair<int, std::set<int>> new_pair;
        new_pair.first = i;
        adjacency_list.insert(new_pair);
    }

    get_unordered_adjacency_list(adjacency_list, in, num_edges);

    auto components = get_connected_components(adjacency_list);

    std::map<int, std::set<int>> sorted_components;
    for (auto& component : components) { 
        sorted_components.insert(std::make_pair(*component.second.begin(), component.second));
    }

    out << sorted_components.size() << std::endl;
    for (const auto& component : sorted_components) {
        for (int vertex : component.second) {
            out << vertex << " ";
        }
        out << std::endl;
    }

    in.close();
    out.close();
}