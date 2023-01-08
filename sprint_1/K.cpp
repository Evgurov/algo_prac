# include <iostream>
# include <fstream>
# include <vector>

std::vector<int> reverse_vec(std::vector<int> &vec){
    int length = vec.size();
    for (int i = 0; i < length / 2; ++i){
        std::swap(vec[i], vec[length - 1 - i]);
    }

    return vec;
}

std::vector<int> make_list_form(int k){
    std::vector<int> list_form;
    while (k != 0){
        list_form.push_back(k % 10);
        k = k / 10;
    }

    return reverse_vec(list_form);
}

std::vector<int> count_sum(std::vector<int> a, std::vector<int> b){
    int length_a = a.size(), length_b = b.size();
    int number_of_digits_to_pad;
    if (length_a > length_b){
        number_of_digits_to_pad = length_a - length_b;
        std::vector<int> digits_to_pad(number_of_digits_to_pad, 0);
        digits_to_pad.insert(digits_to_pad.end(), b.begin(), b.end());
        b = digits_to_pad;
    } else {
        number_of_digits_to_pad = length_b - length_a;
        std::vector<int> digits_to_pad(number_of_digits_to_pad, 0);
        digits_to_pad.insert(digits_to_pad.end(), a.begin(), a.end());
        a = digits_to_pad;
    }
    int length = a.size();
    std::vector<int> result(length);
    int sum;
    int res = 0;
    for (int i = length - 1; i >= 0; --i){
        sum = a[i] + b[i] + res;
        result[length - 1 - i] = sum % 10;
        res = sum > 9; 
    }
    if (res){
        result.push_back(1);
    }

    return reverse_vec(result);
}

void print_vec(std::vector<int> vec, std::ofstream &out){
    for(int i = 0; i < vec.size(); ++i){
        out << vec[i] << " ";
    }
}


int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");

    int n, k;
    in >> n;
    std::vector<int> list_form(n);

    for (int i = 0; i < n; ++i){
        in >> list_form[i];
    }
    in >> k;

    print_vec(count_sum(list_form, make_list_form(k)), out);

    in.close();
    out.close();
}