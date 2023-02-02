// ID: 81698532
// ============================================================================================================
// Algorithm uses stack for calculation. It goes through all the words in equation and do the following:
//
// 1. If word is an operation sign ("+", "-", "*", "/") then it takes two top elements from stack, performs
// operation with them and puts result on top of the stack.
// 2. If word is not an operation sign then it means that it is a number, so the algorithm makes an integer of
// it and puts the integer on top of the stack.
// 3. When all the words in the input sequence are considered, it is necessary to output the top element of 
// the stack as a result.
//
// This approach emulates the logic of calculation in Postfix Notation.
//
// It is worth mentioning how operation "/" is implemented. If left-hand side is greater than 0 then standart
// C++ '/' operation is used, else if left-hand side is negative then if it is divisible by right-hand side 
// then the standard C++ '/' is used, else if left-hand side is negative and not-divisible by right-hand side
// then we need to substract 1 from the result of standard '/'.
//
// Time complexity: calculate the result the algorithm makes n steps where n is the number of operands and
// operations, and on each step it rather put a number in the stack or take two numbers from it and perform
// simple operation which is O(1). Then time complexity is O(n).
// Memory complexity: my implementation uses memory for string with input equation and vector of words of the
// equation which gives O(n) memory complexity.
// ===========================================================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>
#include <functional>
#include <map>
#include <string>

std::function<int(int,int)> sum_fun = [](int a, int b) { return a + b; };
std::function<int(int,int)> minus_fun = [](int a, int b) { return a - b; };
std::function<int(int,int)> mult_fun = [](int a, int b) { return a * b; };
std::function<int(int,int)> div_fun = [](int a, int b) { return a >= 0 ? a / b : a % b == 0 ? a / b : a / b - 1; };

std::map<std::string, std::function<int(int, int)>> operations {{"+", sum_fun}, {"-", minus_fun}, {"*", mult_fun}, {"/", div_fun}};

std::vector<std::string> split(std::string str){
    std::istringstream ist(str);
    std::vector<std::string> str_splitted;
    for (std::string word; ist >> word; str_splitted.push_back(word)){}
    return str_splitted;
}

int calculate(std::string equation){
    std::vector<std::string> equation_vec = split(equation);
    std::stack<int> calc_stack;
    std::vector<std::string>::iterator iter;
    for (iter = equation_vec.begin(); iter != equation_vec.end(); ++iter){
        if (operations.find(*iter) != operations.end()){
            int a = calc_stack.top(); calc_stack.pop();
            int b = calc_stack.top(); calc_stack.pop();
            calc_stack.push(operations[*iter](b, a));
        } else {
            calc_stack.push(std::stoi(*iter));
        }
    }

    return calc_stack.top();
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    std::string equation;
    getline(in, equation);
    out << calculate(equation);

    in.close();
    out.close();
}