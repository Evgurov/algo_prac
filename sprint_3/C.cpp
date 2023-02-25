#include <iostream>
#include <fstream>

std::ifstream in;
std::ofstream out;

bool is_substring(const std::string& str1, const std::string& str2) {
    auto iter1 = str1.begin();
    auto iter2 = str2.begin();
    while (iter2 != str2.end() && iter1 != str1.end()) {
        if (*iter2 == *iter1){
            iter1++;
            iter2++;
        } else {
            iter2++;
        }
    }
    if (iter1 == str1.end()){
        return true;
    } else {
        return false;
    }
} 

int main(){
    in.open("input.txt");
    out.open("output.txt");

    std::string str1, str2;

    in >> str1 >> str2;

    if (is_substring(str1, str2)) {
        out << "True";
    } else {
        out << "False";
    }

    in.close();
    out.close();
}