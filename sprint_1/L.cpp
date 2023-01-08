# include <iostream>
# include <fstream>
# include <string>
# include <map>

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    std::string s, t;
    in >> s >> t;

    std::map<char, int> letters_counts_s;
    std::map<char, int> letters_counts_t;

    for (int i = 0; i < s.length(); ++i){
        letters_counts_s[s[i]] += 1;
    }

    for (int i = 0; i < t.length(); ++i){
        letters_counts_t[t[i]] += 1;
    }

    char extra_letter;

    std::map<char, int>::iterator t_iter;
    for (t_iter = letters_counts_t.begin(); t_iter != letters_counts_t.end(); t_iter++){
        if (letters_counts_s.find(t_iter -> first) != letters_counts_s.end()){
            if (letters_counts_s[t_iter -> first] != t_iter -> second){
                extra_letter = t_iter -> first;
            }
        } else {
            extra_letter = t_iter -> first;
        }
    }

    out << extra_letter;

    in.close();
    out.close();
}