#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>

using Iterator = std::vector<int>::iterator;
using CIterator = std::vector<int>::const_iterator;

std::vector<int> merge(CIterator left_begin, CIterator left_end, 
						CIterator right_begin, CIterator right_end) {
	std::vector<int> merged_arr(left_end - left_begin + right_end - right_begin);
	Iterator merged_iter = merged_arr.begin();
	CIterator left = left_begin, right = right_begin;
	while (left != left_end && right != right_end) {
		if (*left >= *right) {
			*merged_iter = *right;
			right++;
		} else {
			*merged_iter = *left;
			left++;
		}
		merged_iter++;
	}
	while (left != left_end) {
		*merged_iter = *left;
		left++;
		merged_iter++;
	}
	while (right != right_end) {
		*merged_iter = *right;
		right++;
		merged_iter++;
	}

	return merged_arr;
}

void put_between(Iterator begin, Iterator end, std::vector<int> arr) {
	auto arr_iter = arr.cbegin();
	for (auto iter = begin; iter != end; iter++){
		*iter = *arr_iter;
		arr_iter++;
	}
}

void merge_sort(Iterator begin, Iterator end) {
	if (std::distance(begin, end) > 1){
		Iterator middle = begin + std::distance(begin, end) / 2;
		merge_sort(begin, middle);
		merge_sort(middle, end);
		put_between(begin, end, merge(begin, middle, middle, end));
	}
}

void test_merge_sort() {
	std::vector<int> a = {1, 4, 9};
	std::vector<int> b = {2, 10, 11};
	std::vector<int> c = merge(a.cbegin(), a.cend(), b.cbegin(), b.cend());
	std::vector<int> expected = {1, 2, 4, 9, 10, 11};
	assert(c == expected);
	std::vector<int> d = {1, 4, 2, 10, 1, 2};
	std::vector<int> sorted = {1, 1, 2, 2, 4, 10};
	merge_sort(d.begin(), d.end());
	assert(d == sorted);
}