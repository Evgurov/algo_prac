// ID: 85229290
// ================================================================================
// Function `remove(root, key)` works as follows: 
// 1. Find parent of the node which should be deleted (`find_node_parent` function)
//   * If there is no node with such `key` then do nothing.
// 2. Figure out whether the node being deleted is left or right child of its 
// parent. Then form a new subtree on the left or on the right side of the parent
// without deleted node. (`make_new_subtree` function)
//   * For this find the parent of the node which should replace the node being
//   deleted. This is the rightmost node in the left subtree or the leftmost node
//   in the right one. (`find_replacing_node_parent` function) 
//   * Then replace the deleted node with replacing node.
//     > If it is in the left subtree of deleted node then it is right child of its
//     parent, and vice versa.
// 3. If the node being deleted is the root then form a new subtree without this 
// node and this will be the resulting tree.
// --------------------------------------------------------------------------------
// Time complexity: 
// * `find_node_parent` ~ O(log n)
// * `find_replacing_node_parent` ~ O(log n) => `make_new_subtree` ~ O(log n)
// * Then overall time complexity for `remove` ~ O(log n) + O(log n) ~ O(log n)
// Memory complexity: O(1)
// ================================================================================



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
#include <cassert>

Node* find_node_parent(Node* root, Node* parent, int key) {
    // node not found
    if (root == nullptr) {
        return nullptr;
    }
    // should continue searching in the left subtree
    if (root -> value < key) {
        return find_node_parent(root -> right, root, key);
    } 
    // node found, return its parent
    if (root -> value == key) {
        return parent;
    }
    // should continue searching in the right subtree
    if (root -> value >= key) {
        return find_node_parent(root -> left, root, key);
    }

    return nullptr;
}

Node* find_replacing_node_parent(Node* node_to_replace) {
    Node* replacing_node_parent = node_to_replace;
    // if the LEFT subtree is not `nullptr`, find the replacing node in it, return its parent
    if (node_to_replace -> left != nullptr) {
        Node* replacing_node = node_to_replace -> left;
        while (replacing_node -> right != nullptr) {
            replacing_node_parent = replacing_node;
            replacing_node = replacing_node -> right;
        }
        return replacing_node_parent;
    }
    // if the RIGHT subtree is not `nullptr`, find the replacing node in it, return its parent
    if (node_to_replace -> right != nullptr) {
        Node* replacing_node = node_to_replace -> right;
        while (replacing_node -> left != nullptr) {
            replacing_node_parent = replacing_node;
            replacing_node = replacing_node -> left;
        }
        return replacing_node_parent;
    }

    // if `node_to_replace` is a leaf return `nullptr`
    return nullptr;
}

Node* make_new_subtree(Node* node_to_delete) {
    Node* replacing_node_parent = find_replacing_node_parent(node_to_delete);
    Node* replacing_node;
    // if node_to_delete is a leaf
    if (replacing_node_parent == nullptr) {
        return nullptr;
    }
    // if new root can be found on the left side
    if (node_to_delete -> left != nullptr) {
        if (replacing_node_parent == node_to_delete) {
            replacing_node = replacing_node_parent -> left;
            replacing_node_parent -> left = replacing_node -> left;
        } else {
            replacing_node = replacing_node_parent -> right;
            if (replacing_node -> left != nullptr) {
                replacing_node_parent -> right = replacing_node -> left;
            } else {
                replacing_node_parent -> right = nullptr;
            }
        }
    // if new root can be found only on the right side
    } else {
        if (replacing_node_parent == node_to_delete) {
            replacing_node = replacing_node_parent -> right;
            replacing_node_parent -> right = replacing_node -> right;
        } else {
            replacing_node = replacing_node_parent -> left;
            if (replacing_node -> right != nullptr) {
                replacing_node_parent -> left = replacing_node -> right;
            } else {
                replacing_node_parent -> left = nullptr;
            }
        }   
    }

    replacing_node -> left = node_to_delete -> left;
    replacing_node -> right = node_to_delete -> right;

    return replacing_node;
}

Node* remove(Node* root, int key) {
    Node* node_to_delete_parent = find_node_parent(root, root, key);

    // if there is no node with `value = key`
    if (node_to_delete_parent == nullptr) { 
        return root;
    }

    // if the node which should be deleted is NOT the root

    // if node_to_delete is left child of its parent 
    if ((node_to_delete_parent -> left != nullptr) && 
        (node_to_delete_parent -> left -> value == key)) {
        Node* node_to_delete = node_to_delete_parent -> left;
        node_to_delete_parent -> left = make_new_subtree(node_to_delete);
    }

    // if node_to_delete is right child of its parent
    else if ((node_to_delete_parent -> right != nullptr) &&
        (node_to_delete_parent -> right -> value == key)) {
        Node* node_to_delete = node_to_delete_parent -> right;
        node_to_delete_parent -> right = make_new_subtree(node_to_delete);
    }

    // if the node which should be deleted is the root
    else {
        root = make_new_subtree(root);
    }
    
    return root;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node1({nullptr, nullptr, 2});
    Node node2({&node1, nullptr, 3});
    Node node3({nullptr, &node2, 1});
    Node node4({nullptr, nullptr, 6});
    Node node5({&node4, nullptr, 8});
    Node node6({&node5, nullptr, 10});
    Node node7({&node3, &node6, 5});
    Node* newHead = remove(&node7, 10);
    assert(newHead->value == 5);
    assert(newHead->right == &node5);
    assert(newHead->right->value == 8);
}

int main() {
  test();
}
#endif