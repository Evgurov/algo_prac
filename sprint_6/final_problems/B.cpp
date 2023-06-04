// ID:86426066
// =============================================================================
// Map is optimal <=> in graph with reversed edges marked with 'R' there is a
// cycle. Then algorithm works as follows:
// * Make the adjacency list, reversing all 'R' edges.
// * Launch BFS to find a cycle in this graph.
// It is actually needed to lauch BFS for every "connected component" of the 
// graph so for the sake of optimality algorithm stores the visited vertices and 
// launches BFS with only not visited vertices as a starting ones.
// Existance of a cycle is checked as follows:
// * If the new vertex to push into the stack is grey then it is cycle.
// -----------------------------------------------------------------------------
// Time complexity: O(|E| + |V|) for single BFS iteration (if graph is fully-
// connected). Overall complecity depends on graph connectivity
// Memory complexity: O(|V| + |E|) for adjacency list, O(|V|) for the array of
// visited vertices, O(|V|+|E|) for callstack.

#include <iostream>
#include <fstream>

#include <limits>

#include <stack>
#include <vector>

enum Color {white, grey, black};

void make_adjacency(
    std::istream& in,
    std::vector<std::vector<int>>& adjacency,
    int n) {
    
    char road_type;
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < n - i; ++j) {
            in >> road_type;
            switch (road_type)
            {
            case 'R':
                adjacency[i + j].push_back(i);
                break;
            case 'B':
                adjacency[i].push_back(i + j);
                break;
            }
        }
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

bool find_cycle(const std::vector<std::vector<int>>& adjacency, std::vector<bool>& visited, int start) {
    std::stack<int> callstack;
    std::vector<Color> vertex_colors(adjacency.size(), white);

    callstack.push(start - 1);
    while (!callstack.empty()) {
        int cur_vertex = callstack.top();
        if (vertex_colors[cur_vertex] == black) {
            callstack.pop();
        }
        if (vertex_colors[cur_vertex] == grey) {
            callstack.pop();
            vertex_colors[cur_vertex] = black;
            visited[cur_vertex] = true;
        }
        if (vertex_colors[cur_vertex] == white) {
            vertex_colors[cur_vertex] = grey;
            for (const auto& adj_vertex : adjacency[cur_vertex]) {
                if (vertex_colors[adj_vertex] == grey) {
                    return true;
                }
                if (vertex_colors[adj_vertex] == white) {
                    callstack.push(adj_vertex);
                }
            }
        }
    }

    return false;
}

int main() {
    std::ifstream in;
    std::ofstream out;

    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<std::vector<int>> adjacency(n);

    make_adjacency(in, adjacency, n);
    std::vector<bool> visited (n, false);

    bool cycle_found = false;
    for (int start = 1; start <= n; ++start) {
        if (!visited[start - 1]) {
            if (find_cycle(adjacency, visited, start)) {
                cycle_found = true;
                break;
            }
        }
    }

    if (cycle_found) {
        out << "NO";
    } else {
        out << "YES";
    }

    in.close();
    out.close();
}