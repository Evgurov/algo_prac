# include <iostream>
# include <fstream>
# include <string>
# include <stack>

bool palindrome_stack(std::string text){
    bool result = true;

    std::stack<int> my_stack;

    int size = text.length();

    int i = 0;
    for (i; i < size / 2; ++i){
        my_stack.push(text[i]);
    }
    if (size % 2 == 1){
        i++;
    }
    char sym;
    for (i; i < size; ++i){
        sym = my_stack.top();
        my_stack.pop();
        if (sym != text[i]){
            result = false;
            break;
        }
    }
    return result;
}

bool palindrome_pointers(std::string text){
    bool result = true;
    std::string::iterator left = text.begin(), right = text.end() - 1;
    while (right - left > 0){
        if (*left != *right){
            result = false;
            break;
        }
        left++;
        right--;
    }
    return result;
}


int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    std::string text;
    char sym;
    while (in.get(sym)){
        if (sym >= 'a' && sym <= 'z'){
            text += sym;
        }
        if (sym >= 'A' && sym <= 'Z'){
            sym += 32;
            text += sym;
        }
    }

    if (palindrome_pointers(text)){
        out << "True";
    } else {
        out << "False";
    }

    in.close();
    out.close();
}