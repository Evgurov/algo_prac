#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Heap {
    long c;
    long m;
    bool operator< (const Heap& second_heap) const {return c > second_heap.c;}
};

int main() {
    std::ifstream in;
    std::ofstream out;

    in.open("input.txt");
    out.open("output.txt");

    int M, n;
    in >> M >> n;
    std::vector<Heap> heaps (n);
    for (auto& heap : heaps) {
        in >> heap.c >> heap.m;
    }

    std::sort(heaps.begin(), heaps.end());

    long total_cost = 0; 
    long space_left = M;
    for (const auto& heap : heaps) {
        if (heap.m > space_left) {
            total_cost += heap.c * space_left;
            break;
        }
        
        total_cost += heap.c * heap.m;
        space_left -= heap.m;
    }

    out << total_cost;

    in.close();
    out.close();
}