/*************************************************************************
	> File Name: 6.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 20 Aug 2022 01:25:32 PM CST
 ************************************************************************/

#include<iostream>
#include <vector>
#include <stack>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void ListNode_append(ListNode *head, int val) {
    ListNode *pNew = new ListNode(val);
    if(head == NULL) head = pNew;
    else {
        ListNode *node = head;
        while(node->next != NULL) node = node->next;
        node->next = pNew;
    }
}

class Solution {
public:
    vector<int> reversePrint(ListNode *head);
};

vector<int> Solution::reversePrint(ListNode *head) {
    vector<int> result;
    stack<int> st;
    ListNode *cur = head;
    while(cur != NULL) {
        st.push(cur->val);
        cur = cur->next;
    }
    while(!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }
    return result;
}

int main() {
    int x;
    cin >> x;
    ListNode *head = new ListNode(x);
    while(1) {
        cin >> x;
        ListNode_append(head, x);
        if(cin.get() == '\n') break;
    }
    Solution t1;
    vector<int> result = t1.reversePrint(head);
    int n = result.size();
    for(int i = 0; i < n; ++i) {
        if(i != 0) cout << " ";
        cout << result[i];
    }
    cout << endl;
    return 0;
}
