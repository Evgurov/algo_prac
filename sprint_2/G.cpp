#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define INFTY -2147483648

class Stack {
private:
    std::vector<int> data;
    std::vector<int> max_elems;
public:
    Stack(): data(), max_elems() {};
    void push(int);
    bool pop();
    int get_max();
};

int Stack::get_max(){
    if (!max_elems.empty()){
        return max_elems.back();
    } else {
        return INFTY;
    }
}

void Stack::push(int elem){
    data.push_back(elem);
    if (max_elems.empty()){
        max_elems.push_back(elem);
    } else if (elem >= max_elems.back()){
        max_elems.push_back(elem);
    }
}

bool Stack::pop(){
    if (data.size() == 0){
        return false;
    } else {
        int elem_to_pop = data.back();
        data.pop_back();
        if (max_elems.back() == elem_to_pop){
            max_elems.pop_back();
        }
        return true;
    }
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;

    Stack my_stack;

    std::string command;
    int param;

    for (int i = 0; i < n; ++i){
        in >> command;
        if (command == "push"){
            in >> param;
            my_stack.push(param);
        } else if (command == "pop"){
            if (!my_stack.pop()){
                out << "error\n";
            }
        } else if (command == "get_max"){
            int max_elem = my_stack.get_max();
            if (max_elem == INFTY){
                out << "None\n";    
            } else {
                out << max_elem << std::endl;
            }
        }
    }

    in.close();
    out.close();
}