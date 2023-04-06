#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  const Node* left = nullptr;  
  const Node* right = nullptr;
  Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
};  
#endif

#ifdef REMOTE_JUDGE
#include "solution_tree.h"
#endif
#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;

int count_depth(const Node* root) {
    if (root == nullptr) {
        return 0;
    }

    int depth_left = count_depth(root -> left);
    int depth_right = count_depth(root -> right);

    if (depth_left == -1 || depth_right == -1 || abs(depth_left - depth_right) > 1) {
        return -1;
    }

    return max(depth_left, depth_right) + 1;
}

bool Solution(const Node* root) {
    if (count_depth(root) == -1) {
        return false;
    }

    return true;
} 


#ifndef REMOTE_JUDGE
void test() {
    Node node1({1, nullptr, nullptr});
    Node node2({-5, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({10, nullptr, nullptr});
    Node node5({2, &node3, &node4});
    assert(Solution(&node5));
}

int main() {
  test();
}
#endif