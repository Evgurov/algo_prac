#include <iostream>
#include <fstream>
#include <vector>

std::ifstream in;
std::ofstream out;

struct Participant {
    const std::string login;
    const unsigned problems_solved;
    const unsigned penalty;

    Participant(std::string& login, unsigned problems_solved, unsigned penalty) : 
        login(login), problems_solved(problems_solved), penalty(penalty) {} ;

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

    if (login > second.login)
        return true;
    if (login < second.login)
        return false;

    return false;
}

template <class T>
class Heap {
    std::vector<T> heap;
    size_t heap_size;
public:
    Heap() : heap(1), heap_size() {};
    void add(const T& elem);
    void remove(const T& elem);
    T get_min() {return heap[1]};
};

template <class T>
void Heap<T>::add(const T& elem) {
    heap.push_back(elem);
    heap_size++;
    int idx = heap_size;
    while (idx > 1 && heap[idx] < heap[idx/2]) {
        std::swap(heap[idx], heap[idx/2]);
        idx = idx/2;
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

        while(idx <= heap_size) {
        if (idx * 2 < heap_size) {
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
    }
}

template <class Iterator>
void heap_sort(Iterator begin, Iterator end) {

}

int main(){
    in.open("input.txt");
    out.open("output.txt");

    unsigned participants_number;
    in >> participants_number;

    std::vector<Participant> participants;

    std::string login;
    unsigned problems_solved, penalty;

    for (Participant& participant : participants) {
        in >> login >> problems_solved >> penalty;
        participants.push_back(Participant(login, problems_solved, penalty));
    }

    heap_sort(participants.begin(), participants.end());

    for (unsigned i = participants.size(); i-- > 0; ) {
        out << participants[i].login << std::endl;
    }

    in.close();
    out.close();
}