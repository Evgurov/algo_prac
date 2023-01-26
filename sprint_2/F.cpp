#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define INFTY -2147483648

class Stack {
private:
    std::vector<int> data;
    int max_elem;
public:
    Stack(): data(), max_elem(INFTY) {};
    void push(int);
    bool pop();
    int get_max();
};

int Stack::get_max(){
    return max_elem;
}

void Stack::push(int elem){
    data.push_back(elem);
    if (elem > max_elem){
        max_elem = elem;
    }
}

bool Stack::pop(){
    if (data.size() == 0){
        return false;
    } else {
        data.pop_back();
        if (data.size() != 0){
            int new_max_elem = data[0];
            for (std::vector<int>::iterator iter = data.begin(); iter != data.end(); iter++){
                if (*iter > new_max_elem){
                    new_max_elem = *iter;
                }
            }
            max_elem = new_max_elem;
        } else {
            max_elem = INFTY;
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