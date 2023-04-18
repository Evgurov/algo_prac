#include <iostream>
#include <fstream>

#include <vector>

#include <unordered_map>

#include <set>
#include <unordered_set>

#include <stack>

std::ifstream in;
std::ofstream out;

template<class VertexType>
auto get_adgacency_list(std::istream& in, int num_edges) {
    std::unordered_map<VertexType, std::set<VertexType>> adjacency_list;
    VertexType v, u;
    for (int i = 0 ; i < num_edges; ++i) {
        in >> u >> v;
        adjacency_list[u].insert(v);
    }

    return adjacency_list;
}

template <class VertexType, class EnterTimingType = unsigned, class LeaveTimingType = unsigned >
auto DFS_with_timings(std::unordered_map<VertexType, std::set<VertexType>>& adjacency_list, VertexType start) {
    std::stack<VertexType> callstack;

    enum Color {white, grey, black};
    std::unordered_map<VertexType, Color> vertex_colors;

    std::unordered_map<VertexType, std::pair<EnterTimingType, LeaveTimingType>> timings;

    unsigned cur_timing = 0;

    callstack.push(start);
    while (!callstack.empty()) {
        VertexType cur_vertex = callstack.top();
        if (vertex_colors[cur_vertex] == black) {
            callstack.pop();
        }
        if (vertex_colors[cur_vertex] == grey) {
            callstack.pop();
            vertex_colors[cur_vertex] = black;
            timings[cur_vertex].second = cur_timing;
            cur_timing++;
        }
        if (vertex_colors[cur_vertex] == white) {
            vertex_colors[cur_vertex] = grey;
            timings[cur_vertex].first = cur_timing;
            for (auto iter = adjacency_list[cur_vertex].rbegin(); iter != adjacency_list[cur_vertex].rend(); iter++) {
                if (vertex_colors[*iter] != grey && vertex_colors[*iter] != black) {
                    callstack.push(*iter);
                }
            }
            cur_timing++;
        }
    }

    return timings;
}

int main() {
    in.open("input.txt");
    out.open("output.txt");

    int num_vertices, num_edges;
    in >> num_vertices >> num_edges;

    auto adjacency_list = get_adgacency_list<int>(in, num_edges);

    int start = 1;
    auto timings = DFS_with_timings(adjacency_list, start);

    for (int i = 1; i <= num_vertices; ++i) {
        out << timings[i].first << " " << timings[i].second << std::endl;
    }

    in.close();
    out.close();
}