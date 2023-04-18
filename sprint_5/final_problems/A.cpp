// ID: 85467569
// ==============================================================================
// `heap_sort` function creates a heap for sorting. It adds all elements of an
// array to heap and then on every step gets the smallest one, forming new sorted
// array.
// ------------------------------------------------------------------------------
// Class `Heap` is implemented as min-heap structure with the smallest element on
// top. It contains the following methods:
// * void add(T elem) -- adds new element to the heap via siftup procedure
//   > time complexity: O(log n)
// * void remove(T elem) -- deletes elem from heap if there is one
//   > time complexity: O(log n)
// * T get_mini() -- return the minimal element in the heap (top one) 
//   > time complexity: O(1)
// ------------------------------------------------------------------------------
// Time complexity: n * O(log n) ~ O(n log n)
// Memory complexity: O(n)
// ==============================================================================



#include <iostream>
#include <fstream>
#include <vector>

std::ifstream in;
std::ofstream out;

struct Participant {
    std::string login;
    unsigned problems_solved;
    unsigned penalty;

    bool operator < (const Participant& second) const ;
    bool operator == (const Participant& second) const {return login == second.login;} ;
};

bool Participant::operator < (const Participant& second) const {
    if (problems_solved < second.problems_solved)
        return true;
    if (problems_solved > second.problems_solved)
        return false;

    if (penalty > second.penalty)
        return true;
    if (penalty < second.penalty)
        return false;

    return login > second.login;
}

template <class T>
int find_min_idx(std::vector<T>& arr, int idx_1, int idx_2, int idx_3) {
    int min_idx = idx_1;
    if (arr[idx_2] < arr[min_idx]) {
        min_idx = idx_2;
    }
    if (arr[idx_3] < arr[min_idx]) {
        min_idx  = idx_3;
    }

    return min_idx;
}

template <class T>
class Heap {
    std::vector<T> heap;
    size_t heap_size;
public:
    Heap() : heap(1), heap_size() {};
    void add(const T& elem);
    void remove(const T& elem);
    T get_min() {return heap[1];};
};

template <class T>
void Heap<T>::add(const T& elem) {
    heap.push_back(elem);
    heap_size++;
    int idx = heap_size;
    while (idx > 1 && heap[idx] < heap[idx / 2]) {
        std::swap(heap[idx], heap[idx / 2]);
        idx = idx / 2;
    }
}

template <class T>
void Heap<T>::remove(const T& elem) {
    int idx = 1;
    while (idx <= heap_size) {
        if (heap[idx] == elem) {
            break;
        } else {
            idx++;
        }
    }
    if (idx <= heap_size) {
        heap[idx] = heap[heap_size];
        heap.pop_back();
        heap_size--;

        while(idx <= heap_size) {
            if (idx * 2 <= heap_size) {
                if (idx * 2 + 1 <= heap_size) {
                    int min_idx = find_min_idx(heap, idx, idx * 2, idx * 2 + 1);
                    if (min_idx != idx) {
                        std::swap(heap[idx], heap[min_idx]);
                        idx = min_idx;
                    } else {
                        break;
                    }
                } else {
                    if (heap[idx * 2] < heap[idx]) {
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
    }
}

template <class T>
void heap_sort(std::vector<T>& arr) {
    Heap<T> heap;
    auto iter = arr.cbegin();
    while (iter != arr.cend()) {
        heap.add(*iter);
        iter++;
    }

    for (auto& elem : arr) {
        T min_elem = heap.get_min();
        elem = min_elem;
        heap.remove(min_elem);
    }
}

int main(){
    in.open("input.txt");
    out.open("output.txt");

    unsigned participants_number;
    in >> participants_number;

    std::vector<Participant> participants(participants_number);

    for (Participant& participant : participants) {
        in >> participant.login
           >> participant.problems_solved
           >> participant.penalty;
    }

    heap_sort(participants);

    for (unsigned i = participants.size(); i-- > 0; ) {
        out << participants[i].login << std::endl;
    }

    in.close();
    out.close();
}