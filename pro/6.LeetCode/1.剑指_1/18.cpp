/*************************************************************************
	> File Name: 18.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 13 Sep 2022 09:51:58 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

typedef struct Node {
    int val;
    struct Node *next;
}Node, *LinkedList;

LinkedList insert(LinkedList head, Node *node) {
    if(head == NULL) {
        head = node;
        return head;
    }
    Node *current_node = head;
    while(current_node->next != NULL) current_node = current_node->next;
    current_node->next = node;
    return head;
}

void output(LinkedList head) {
    if(head == NULL) return ;
    Node *current_node = head;
    while(current_node != NULL) {
        cout << current_node->val << " ";
        current_node = current_node->next;
    }
    cout << endl;
}

void clear(LinkedList head) {
    Node *current_node = head;
    while(current_node != NULL) {
        Node *delete_node = current_node;
        current_node = current_node->next;
        free(delete_node);
    }
}

class Solution {
public:
    LinkedList deleteNode(LinkedList head, int val);
};

LinkedList Solution::deleteNode(LinkedList head, int val) {
    Node *current_node = head;
    Node *delete_node = head;
    if(head->val == val) {
        head = head->next;
        free(current_node);
        return head;
    }
    while(current_node != NULL && current_node->val != val) {
        delete_node = current_node;
        current_node = current_node->next;
    }
    if(current_node != NULL) {
        delete_node->next = current_node->next;
        free(current_node);
    }
    return head;
}

int main() {
    int val;
    LinkedList head = NULL;
    while(1) {
        cin >> val;
        Node *node = (Node *)malloc(sizeof(Node));
        node->val = val;
        node->next = NULL;
        head = insert(head, node);
        if(cin.get() == '\n') break;
    }
    output(head);
    cin >> val;
    Solution t1;
    head = t1.deleteNode(head, val);
    output(head);
    clear(head);
    return 0;
}
