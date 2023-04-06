#include <vector>
#include <cassert>
#ifdef REMOTE_JUDGE
#include "solution.h"
#endif

int get_max_idx(std::vector<int>& vec, int idx_1, int idx_2) {
    if (vec[idx_1] > vec[idx_2]) {
        return idx_1;
    } else {
        return idx_2;
    }
}

int siftDown(std::vector<int>& heap, int idx) {
    while(idx <= heap.size()) {
        if (idx * 2 < heap.size()) {
            if (idx * 2 + 1 < heap.size()) {
                int max_idx = get_max_idx(heap, idx * 2, idx * 2 + 1);
                if (heap[idx] < heap[max_idx]) {
                    std::swap(heap[idx], heap[max_idx]);
                    idx = max_idx;
                } else {
                    break;
                }
            } else {
                if (heap[idx] < heap[idx * 2]) {
                    std::swap(heap[idx], heap[idx * 2]);
                    idx = idx * 2;
                } else {
                    break;
                }
            }
        } else {
            break;
        }
    }

    return idx;
}

#ifndef REMOTE_JUDGE
void test() {
    std::vector<int> sample = {-1, 12, 1, 8, 3, 4, 7};
    assert(siftDown(sample, 2) == 5);
}


int main() {
    test();
}
#endif