#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <map>

std::map<char, int> opening_brackets{{'(', 1}, {'[',2}, {'{', 3}};
std::map<char, int> closing_brackets{{')', 1}, {']',2} , {'}', 3}};

bool right_bracket_seq(const std::string &bracket_seq){
    std::stack<char> brackets_stack;
    for (int i = 0; i < bracket_seq.length(); ++i){
        char bracket = bracket_seq[i];
        if (opening_brackets.find(bracket) != opening_brackets.end()){
            brackets_stack.push(opening_brackets[bracket]);
        } else if (closing_brackets.find(bracket) != closing_brackets.end()){
            if (!brackets_stack.empty() && (brackets_stack.top() == closing_brackets[bracket])){
                brackets_stack.pop();
            } else {
                return false;
            }
        }
    }
    if (brackets_stack.empty()){
        return true;
    } else {
        return false;
    }
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    std::string bracket_seq;

    in >> bracket_seq;

    if (right_bracket_seq(bracket_seq)){
        out << "True";
    } else {
        out << "False";
    }

    in.close();
    out.close();
}