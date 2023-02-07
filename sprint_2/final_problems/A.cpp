// ID: 81966029
// ========================================================================================================
// Class 'deq' is based on cycled array approach. Class contains field 'data' --- array with contents of
// deq, fields 'max_size' and 'cur size' with maximum size of deq and current size of deq(Maximum size
// of deq is equal to size of array in 'data'), and fields 'head' and 'tail' with indeces in 'data' where
// first and last element of queue are. 
//
// It is important to mention that for 'head' and 'tail' pointers here standard C++ covention is used --- 
// 'head' points to FIRST element and 'tail' points AFTER THE LAST ONE. This contributes to the conciseness
// and uniformity of 'push' and 'pop' methods. The only exception is when queue is empty, then head = tail
//
// To keep this invariant we should:
//
// 1. For push_back: rewrite *tail then move tail cyclically to the right
// 2. For push_front: move head cyclically to the left then rewrite *head
// 3. For pop_back: move tail to the left cyclically then return *tail
// 4. For pop_front: return *head then move head to the right cyclically
// 
// Time complexity: all push-pop operations are O(1)
// Memory complexity: O(n) 
// ========================================================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

std::ifstream in;
std::ofstream out;

enum commands {PUSH_BACK, PUSH_FRONT, POP_BACK, POP_FRONT};
std::map<std::string, commands> str_to_commands {
    {"push_back", PUSH_BACK}, 
    {"push_front", PUSH_FRONT}, 
    {"pop_back", POP_BACK},
    {"pop_front", POP_FRONT} 
};

class Deque {
    std::vector<int> data;
    int max_size;
    int cur_size;
    int head;
    int tail;
public:
    Deque(int max_size) : data(max_size), max_size(max_size), cur_size(), head(), tail() {}
    void push_back(int);
    void push_front(int);
    int pop_back();
    int pop_front();
};

void Deque::push_back(int value){
    if (cur_size == max_size){
        throw "error";
    }
    data[tail] = value;
    tail = (tail + 1) % max_size;
    cur_size++;
}

void Deque::push_front(int value){
    if (cur_size == max_size){
        throw "error";
    }
    head = (head - 1 + max_size) % max_size;
    data[head] = value;
    cur_size++;
}

int Deque::pop_back(){
    if (cur_size == 0){
        throw "error";
    }
    tail = (tail - 1 + max_size) % max_size;
    int element_to_pop = data[tail];
    cur_size--;
    
    return element_to_pop;
}

int Deque::pop_front(){
    if (cur_size == 0){
        throw "error";
    }
    int element_to_pop = data[head];
    head = (head + 1) % max_size;
    cur_size--;
    
    return element_to_pop;
}

void process_instructions(int number_of_instructions, Deque &my_deq){
    std::string instruction;
    int param;
    for (int i = 0; i < number_of_instructions; ++i){
        in >> instruction;
        try{
            switch (str_to_commands[instruction])
            {
            case PUSH_BACK:
                in >> param;
                my_deq.push_back(param);
                break;
            case PUSH_FRONT:
                in >> param;
                my_deq.push_front(param);
                break;
            case POP_BACK:
                out << my_deq.pop_back() << std::endl; 
                break;
            case POP_FRONT:
                out << my_deq.pop_front() << std::endl; 
                break;
            default:
                break;
            }
        } catch(const char* msg) {
            out << msg << std::endl;
        }
    }
}

int main(){
    in.open("input.txt");
    out.open("output.txt");

    int number_of_instructions, max_size;
    in >> number_of_instructions >> max_size;
    
    Deque my_deq(max_size);

    process_instructions(number_of_instructions, my_deq);

    in.close();
    out.close();
}