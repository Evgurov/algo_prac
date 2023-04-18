#include <iostream>
#include <fstream>

#include <set>
#include <unordered_set>

#include <unordered_map>

#include <stack>

std::ifstream in;
std::ofstream out;

template<class VertexType>
std::unordered_map<VertexType, std::set<VertexType>>
get_unordered_adgacency_list(std::istream& in, int num_edges) {
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
void DFS(std::unordered_map<VertexType, std::set<VertexType>>& adjacency_list, VertexType start) {
    std::stack<VertexType> callstack;
    std::unordered_set<VertexType> visited_vertices;

    callstack.push(start);
    while (!callstack.empty()) {
        VertexType cur_vertex = callstack.top();
        if (visited_vertices.find(cur_vertex) != visited_vertices.end()) {
            callstack.pop();
        } else {
            visited_vertices.insert(cur_vertex);
            out << cur_vertex << " ";
            for (auto iter = adjacency_list[cur_vertex].rbegin(); iter != adjacency_list[cur_vertex].rend(); iter++) {
                callstack.push(*iter);
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

    DFS(adjacency_list, start);

    in.close();
    out.close();
}