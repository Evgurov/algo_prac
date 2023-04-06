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
#include <limits>

using namespace std;

const int INFTY = std::numeric_limits<int>::max();
const int MIN_INFTY = std::numeric_limits<int>::min();

int low_bound = MIN_INFTY, upper_bound = INFTY;

bool Solution(const Node* root) {
    if (root == NULL) {
        return true;
    } else {
        if ((root -> value > upper_bound) || (root -> value <= low_bound)) {
            return false;
        }
    }

    int old_low_bound = low_bound;
    int old_upper_bound = upper_bound;

    upper_bound = root -> value;
    low_bound = old_low_bound;
    bool left = Solution(root -> left);

    low_bound = root -> value;
    upper_bound = old_upper_bound;
    bool right = Solution(root -> right);

    return left && right;
} 


#ifndef REMOTE_JUDGE
void test() {
    {
      Node node1({1, nullptr, nullptr});
      Node node2({4, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(Solution(&node5));
    }
    {
      Node node1({1, nullptr, nullptr});
      Node node2({5, nullptr, nullptr});
      Node node3({3, &node1, &node2});
      Node node4({8, nullptr, nullptr});
      Node node5({5, &node3, &node4});
      assert(!Solution(&node5));
    }
}


int main() {
  test();
}
#endif