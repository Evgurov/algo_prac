// ID: 82927752
// =====================================================================
// ALgorithm is implemented via recursive function `inplace_quicksort`. 
// On each step of the recursion two-pointers approach is used to divide
// the array into two parts, where all elements in left part are less or
// equal to some pivot element and all elements in right part are greater
// or equal to pivot. 
//
// RECURSION STEP:
// ---------------------------------------------------------------------
// Sorting function accepts two pointers: `begin` and `end` of the array.
// Here standard C++ half-opened interval approach is used. 
// 
// Firstly, the pivot element is selected randomly among array elements,
// then `left` pointer is set to the first element, and `right` pointer
// to the last elemet of the array. 
// Until `left` pointer is on ther right-hand side of `right` pointer 
// algorithm compares values under left and right pointers with pivot 
// element. While left value is strictly less than pivot, left pointer is
// moved to the next element, and similarly, while right element
// is strictly greater than pivot, right pointer is moved to the previous
// element. Then left and right values are swapped and procedure continues.
// When left pointer "jumps over" right, the procedure stops and the function
// is called recursively with (`begin`, `left`) and (`left`, `end`) 
// arguments.
//
// !NOTION!:
// ----------------------------------------------------------------------
// It is important to stop procedure when `left` pointer is greater than 
// `right` because if array has odd number of elements and pointers meet
// at the same element it is necessary to decide whether it should go to
// the left or right half. If it is greater than pivot only right pointer
// moves and vice versa.
// 
// TIME COMPLEXITY:
// -----------------------------------------------------------------------
// Time complexity is still O(nlog(n))
// 
// MEMORY COMPLEXITY:
// -----------------------------------------------------------------------
// As it is inplace variant of quick sort it uses O(1) additional memory
// on each recursion iteration and O(log(n)) in total.



#include <iostream>
#include <fstream>
#include <random>

std::ifstream in;
std::ofstream out;

struct Participant {
    std::string login;
    unsigned problems_solved;
    unsigned penalty;

    bool operator < (const Participant& second) const;
};

bool Participant::operator < (const Participant& second) const {
    if (problems_solved < second.problems_solved)
        return true;
    if (problems_solved > second.problems_solved)
        return false;

    if (penalty > second.penalty)
        return true;
    if (penalty < second.penalty)
        return false;

    if (login > second.login)
        return true;
    if (login < second.login)
        return false;

    return false;
}

template <typename RandomIt>
void inplace_quicksort(RandomIt begin, RandomIt end) {
    if (std::distance(begin, end) <= 1) {
        return;
    }
    RandomIt pivot_iter = begin + std::rand() % std::distance(begin, end);
    auto pivot = *pivot_iter;
    RandomIt left = begin, right = end - 1;
    while (left <= right) {
        while (*left < pivot && left <= right) {
            left++;
        }
        while (pivot < *right && left <= right) {
            right--;
        }
        if (left <= right) {
            std::swap(*left, *right);
            left++; right--;
        }
    }
    inplace_quicksort(begin, left);
    inplace_quicksort(left, end);
}

int main(){
    in.open("input.txt");
    out.open("output.txt");

    unsigned participants_number;
    in >> participants_number;

    std::vector<Participant> participants(participants_number);

    for (Participant& participant : participants) {
        in >> participant.login
           >> participant.problems_solved
           >> participant.penalty;
    }

    inplace_quicksort(participants.begin(), participants.end());

    for (unsigned i = participants.size(); i-- > 0; ) {
        out << participants[i].login << std::endl;
    }

    in.close();
    out.close();
}