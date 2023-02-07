#include <iostream>
#include <fstream>
#include <vector>

std::ifstream in;
std::ofstream out;

void print_mas(std::vector<int> arr){
    for (int i = 0; i < arr.size(); ++i){
        out << arr[i] << " ";
    }
}

std::vector<int> bubble_sort(std::vector<int> arr){
    bool changed_global = false;
    for (int i = 1; i < arr.size(); ++i){
        bool items_changed = false;
        for (int j = 0; j < arr.size() - i; ++j){
            if (arr[j] > arr[j + 1]){
                std::swap(arr[j], arr[j + 1]);
                items_changed = true;
                changed_global = true;
            }
        }
        if (items_changed){
            print_mas(arr);
            out << std::endl;
        } else {
            break;
        }
    }
    if (!changed_global){
        print_mas(arr);
    }

    return arr;
}

int main(){
    in.open("input.txt");
    out.open("output.txt");

    int n;
    in >> n;

    std::vector<int> arr (n);
    for (int i = 0; i < n; ++i){
        in >> arr[i];
    }

    arr = bubble_sort(arr);

    in.close();
    out.close();
}