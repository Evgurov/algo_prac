#include <iostream>
#include <fstream>
#include <vector>

struct Node {
    int value;
    Node* next;
    Node(int value, Node* next = nullptr): value(value), next(next) {};
};

class List_queue {
    Node* head;
    Node* tail;
    int cur_size;
public:
    List_queue(): head(nullptr), tail(nullptr), cur_size(0) {};
    ~List_queue();
    int get();
    void put(int);
    int get_size();
};

List_queue::~List_queue(){
    Node* cur_node = head;
    while(cur_node != nullptr){
        Node* next_node = cur_node -> next;
        delete cur_node;
        cur_node = next_node;
    }
}

int List_queue::get(){
    if (cur_size == 0){
        throw "error";
    } else if (cur_size == 1){
        int value_to_get = head -> value;
        delete head;
        tail = nullptr;
        head = nullptr;
        cur_size--;
        return value_to_get;
    } else {
        Node* node_to_get = head;
        int value_to_get = node_to_get -> value;
        head = head -> next;
        delete node_to_get;
        cur_size--;
        return value_to_get;
    }
}

void List_queue::put(int elem){
    Node* node_to_put = new Node(elem);
    if (cur_size == 0){
        head = node_to_put;
        tail = node_to_put;
        cur_size++;
    } else {
        tail -> next = node_to_put;
        tail = tail -> next;
        cur_size++;
    }
}

int List_queue::get_size(){
    return cur_size;
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int number_of_instructions;
    in >> number_of_instructions;

    List_queue my_queue;

    std::string command;
    int param;

    for (int i = 0; i < number_of_instructions; ++i){
        in >> command;
        if (command == "put"){
            in >> param;
            my_queue.put(param);
        } else if (command == "get"){
            try {
                out << my_queue.get() << std::endl;
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