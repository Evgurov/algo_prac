#include <iostream>
#include <fstream>

#include <limits>

#include <stack>
#include <vector>

std::ifstream in;
std::ofstream out;

enum Color {white, grey, black};

void make_adjacency(
    std::istream& in,
    std::vector<std::vector<int>>& adjacency,
    int n) {
    
    char road_type;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            in >> road_type;
            switch (road_type)
            {
            case 'R':
                adjacency[i + j + 1].push_back(i + 1);
                break;
            case 'B':
                adjacency[i].push_back(i + j + 2);
                break;
            }
        }
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

bool find_cycle(const std::vector<std::vector<int>>& adjacency) {
    std::stack<int> callstack;
    std::vector<Color> vertex_colors(adjacency.size(), white);

    callstack.push(1);
    while (!callstack.empty()) {
        int cur_vertex = callstack.top();
        if (vertex_colors[cur_vertex - 1] == black) {
            callstack.pop();
        }
        if (vertex_colors[cur_vertex - 1] == grey) {
            callstack.pop();
            vertex_colors[cur_vertex - 1] = black;
        }
        if (vertex_colors[cur_vertex - 1] == white) {
            vertex_colors[cur_vertex - 1] = grey;
            for (const auto& adj_vertex : adjacency[cur_vertex - 1]) {
                if (vertex_colors[adj_vertex - 1] == grey) {
                    return true;
                }
                if (vertex_colors[adj_vertex - 1] == white) {
                    callstack.push(adj_vertex);
                }
            }
        }
    }

    return false;
}

int main() {
    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<std::vector<int>> adjacency(n);

    make_adjacency(in, adjacency, n);

    if (find_cycle(adjacency)) {
        out << "NO";
    } else {
        out << "YES";
    }

    in.close();
    out.close();
}