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
#include <algorithm>

using namespace std;


int Solution(const Node* root) {
    if (root != NULL) {
        int max_children = max(Solution(root -> left), Solution(root -> right));
        if (max_children > root -> value) {
            return max_children;
        } else {
            return root -> value;
        }
    }
    
    return 0;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({1, nullptr, nullptr});
    Node node2({-5, nullptr, nullptr});
    Node node3({3, &node1, &node2});
    Node node4({2, &node3, nullptr});
    assert(Solution(&node4) == 3);
}

int main() {
  test();
}
#endif