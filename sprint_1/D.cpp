# include <iostream>
# include <fstream>
# include <vector>

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("input.txt");
    out.open("output.txt");
    
    int n;
    in >> n;

    std::vector<int> measures(n);

    for (int i = 0; i < n; ++i){
        in >> measures[i];
    }

    int randomness = 0;
    if (n >= 2){
        if (measures[0] > measures[1]){
            randomness += 1;
        }
        if (measures[n-1] > measures[n-2]){
            randomness += 1; 
        }
        for (int i = 1; i < n-1; ++i){
            if (measures[i] > measures[i - 1] && measures[i] > measures[i + 1]){
                randomness += 1;
            }
        }
    }

    if (randomness == 0 && n == 1){
        randomness += 1;
    }

    out << randomness;

    in.close();
    out.close();
    return 0;
}