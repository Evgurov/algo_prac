#ifdef REMOTE_JUDGE
#include "solution.h"
#endif

#ifndef REMOTE_JUDGE
#include <cassert>
#include <string>

struct Node {  
    std::string value;  
    Node* next;  
    Node(const std::string &value, Node* next) : value(value), next(next) {}
};
#endif


Node* solution(Node* head, int idx) {
    Node* node_to_delete;
    if (idx == 0){
        node_to_delete = head;
        head = node_to_delete -> next;
//        delete node_to_delete;
    } else {
        Node* current_node = head;
        for (int i = 0; i < idx - 1; ++i){
            current_node = current_node -> next;
        }
        node_to_delete = current_node -> next;
        current_node -> next = node_to_delete -> next;
//        delete node_to_delete;
    }
    
    return head;
}

#ifndef REMOTE_JUDGE
void test() {
    Node node3("node3", nullptr);
    Node node2("node2", &node3);
    Node node1("node1", &node2);
    Node node0("node0", &node1);
    Node* new_head = solution(&node0, 1);
    assert(new_head == &node0);
    assert(new_head->next == &node2);
    assert(new_head->next->next == &node3);
    assert(new_head->next->next->next == nullptr);
    // result is : node0 -> node2 -> node3
}

int main() {
    test();
}
#endif