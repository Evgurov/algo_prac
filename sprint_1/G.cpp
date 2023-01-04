# include <iostream>
# include <fstream>
# include <string>
# include <stack>

std::string to_binary(int n){
    if (n == 0){
        return "0";
    }
    std::stack<char> my_stack;
    char res;
    while (n != 0){
        res = n % 2;
        my_stack.push(res + '0');
        n = n / 2;
    }
    std::string binary;
    while (!my_stack.empty()){
        binary += my_stack.top();
        my_stack.pop();
    }

    return binary;
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;

    out << to_binary(n);

    in.close();
    out.close();
}