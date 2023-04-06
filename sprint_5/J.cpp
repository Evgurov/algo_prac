#ifndef REMOTE_JUDGE
struct Node {  
  int value;  
  Node* left = nullptr;  
  Node* right = nullptr;
  Node(Node* left, Node* right, int value) : value(value), left(left), right(right) {}
};  
#endif

#ifdef REMOTE_JUDGE
#include "solution.h"
#endif
#include <cmath>
#include <iostream>
#include <cassert>

using namespace std;

void insert_key(Node* root, int key) {
    if (key < root -> value) {
        if (root -> left == nullptr) {
            root -> left = new Node(nullptr, nullptr, key);
        } else {
            insert_key(root -> left, key);
        }
    } else {
        if (root -> right == nullptr) {
            root -> right = new Node(nullptr, nullptr, key);
        } else {
            insert_key(root -> right, key);
        }
    }
}

Node* insert(Node* root, int key) {
    insert_key(root, key);

    return root;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({nullptr, nullptr, 7});
    Node node2({&node1, nullptr, 8});
    Node node3({nullptr, &node2, 7});
    Node* newHead = insert(&node3, 6);
    assert(newHead->left->value == 6);
    assert(newHead == &node3);
}

int main() {
  test();
}
#endif