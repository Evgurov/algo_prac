# include <iostream>
# include <fstream>
# include <vector>
# include <string>

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;

    int pos = 0;
    int max_length = 0;
    int length = 0;
    char sym;
    std::string max_word;
    std::string word;
    in.get(sym); //get '\n'

    while (pos < n){
        length = 0;
        word = "";
        in.get(sym);
        pos++;
        while(sym != ' ' && sym != '\n'){
            length++;
            word += sym;
            pos++;
            in.get(sym);
        }
        if (max_length < length){
            max_length = length;
            max_word = word;
        }
    }

    out << max_word + '\n';
    out << max_length;

    in.close();
    out.close();
}