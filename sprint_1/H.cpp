# include <iostream>
# include <fstream>
# include <string>

std::string reverse_string(std::string str){
    std::string result = str;
    int length = str.length();
    for (int i = 0; i < length / 2; ++i){
        std::swap(result[i], result[length - 1 - i]);
    }
    
    return result;
}

std::string binary_sum(std::string &a, std::string &b){
    int length_a = a.length();
    int length_b = b.length();

    std::string a_padded = a;
    std::string b_padded = b;

    int digits_to_add;
    if (length_a > length_b){
        digits_to_add = length_a - length_b;
        std::string added_digits(digits_to_add, '0');
        b_padded = added_digits + b;
    } else {
        digits_to_add = length_b - length_a;
        std::string added_digits(digits_to_add, '0');      
        a_padded = added_digits + a;
    }

    int new_length = a_padded.length();
    std::string result(new_length, '0');
    char sum, res = 0;
    for (int i = new_length - 1; i >= 0; --i){
        sum = a_padded[i] - '0' + b_padded[i] - '0' + res;
        result[new_length - 1 - i] = (sum % 2) + '0';
        res = sum > 1;
    }
    if (res){
        result += '1';
    }

    result = reverse_string(result);

    return result;
}

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    std::string a, b;
    in >> a >> b;

    out << binary_sum(a, b);

    in.close();
    out.close();
}