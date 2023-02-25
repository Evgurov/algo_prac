// ID: 82927643
//==================================================================================
// Algorithm finds desired element by moving pointer from one elemnt to another.
// Algorithm starts at any element of the array(it can be first element for example)
// and on every step moves the pointer by array.size / 2, then array.size / 4 and 
// so on...
//
// * If current element is greater(less) than target element then move cyclically
// to the left(right) by step_size. Meanwhile if new element is less(greater) than
// current then do nothing(this is how we stay inside the array).
// * Lower the step_size = step_size / 2. If step_size is odd (except 1) then make
// step_size = step_size / 2 + 1. This is important if we start at the beginning of
// the array and the target element is at the end. 
// * Repeat while step_size > 0 
// 
// Time complexity: Algorithm works similarly to binary search, and it's complexity
// is O(log N) in worst case (it makes log N steps in worst case).
// Memory complexity: O(1), algorithm works on given array.
// ================================================================================

#include "solution.h"
#include <vector>
#include <cassert>

int broken_search(const std::vector<int>& vec, int k) {
    int vec_size = vec.size();
    int step = (vec_size + 1) / 2;
    int search_ind = 0, probe_ind;
    while (step != 0){
        if (vec[search_ind] == k){
            return search_ind;
        } else if (vec[search_ind] < k) {
            probe_ind = (search_ind + step) % vec_size;
            if (vec[probe_ind] > vec[search_ind]) {
                search_ind = probe_ind;
            }
        } else if (vec[search_ind] > k) {
            probe_ind = (search_ind - step + vec_size) % vec_size;
            if (vec[probe_ind] < vec[search_ind]) {
                search_ind = probe_ind;
            }
        }
        step = step / 2 + (step > 1) * (step % 2);
    }

    if (vec[search_ind] == k){
        return search_ind;
    } else {
        return -1;
    }
}

void test() {
    std::vector<int> arr = {19, 21, 100, 101, 1, 4, 5, 7, 12};
    assert(6 == broken_search(arr, 5));
}