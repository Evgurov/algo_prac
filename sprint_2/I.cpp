#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class MyQueueSized {
    std::vector<int> data;
    int cur_size;
    int head;
    int tail;
public:
    MyQueueSized(int max_size): data(max_size), cur_size(0), head(0), tail(0) {};
    void push(int);
    int pop();
    int peek();
    int get_size();
};

void MyQueueSized::push(int elem){
    int max_size = data.size();
    if (cur_size == max_size){
        throw "error";
    } else {
        data[tail] = elem;
        tail = (tail + 1) % max_size;
        cur_size++;
    }
}

int MyQueueSized::pop(){
    int max_size = data.size();
    if (cur_size == 0){
        throw "None";
    } else {
        int element_to_pop = data[head];
        head = (head + 1) % max_size;
        cur_size--;
        return element_to_pop;
    }
}

int MyQueueSized::peek(){
    if (cur_size == 0){
        throw "None";
    }
    return data[head];
}


int MyQueueSized::get_size(){
    return cur_size;
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int number_of_instructions, max_size;
    in >> number_of_instructions >> max_size;

    MyQueueSized my_queue(max_size);

    std::string command;
    int param;

    for (int i = 0; i < number_of_instructions; ++i){
        in >> command;
        if (command == "push"){
            in >> param;
            try {
                my_queue.push(param);
            } catch (const char* msg) {
                out << msg << std::endl;
            }
        } else if (command == "pop"){
            try {
                out << my_queue.pop() << std::endl;
            } catch(const char* msg) {
                out << msg << std::endl;
            }
        } else if (command == "peek"){
            try {
                out << my_queue.peek() << std::endl;
            } catch(const char* msg) {
                out << msg << std::endl;
            }
        } else if (command == "size"){
            out << my_queue.get_size() << std::endl;
        }
    }

    in.close();
    out.close();
}