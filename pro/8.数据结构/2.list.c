/*************************************************************************
	> File Name: 2.list.c
	> Author: 
	> Mail: 
	> Created Time: Mon 06 Jun 2022 04:16:11 PM CST
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>

typedef struct Node{
    int val;
    struct Node *next;
}Node;

typedef struct List{
    Node head;
    int len;
}List;

Node *initNode(int val) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->val = val;
    n->next = NULL;

    return n;
}

void freeNode(Node *n) {
    if(n) free(n);
    return ;
}

List *initList() {
    List *l = (List *)malloc(sizeof(List));
    l->head.next = NULL;
    l->len = 0;
    return l;
}

void freeList(List *l) {
    if(!l) return ;
    Node *p = l->head.next;
    Node *k;
    while(p) {
        k = p;
        p = p->next;
        freeNode(k);
    }
    free(l);
    return ;
}

int insertNode(List *l, int idx, Node *n) {
    if(!l) return 0;
    if(idx < 0 || idx > l->len) return 0;
    //找到插入节点的前一个位置
    Node *p = &(l->head);
    while(idx--) p = p->next;
    //插入节点
    n->next = p->next;
    p->next = n;
    //管理节点个数
    l->len++;
    return 1;
}

//插入数值到链表
int insertVal(List *l, int idx, int val) {
    //生成一个新节点
    Node *n = initNode(val);
    if(!insertNode(l, idx, n)) {
        //插入失败的话要再释放刚创建的节点
        freeNode(n);
        return 0;
    }
    return 1;
}

//删除节点
int erase(List *l, int idx) {
    if(!l) return 0;
    if(idx < 0 || idx >= l->len) return 0;
    //找到插入节点的前一个位置
    Node *p = &(l->head);
    while(idx--) p = p->next;
    Node *k = p->next;
    p->next = p->next->next;

    freeNode(k);
    l->len--;
    return 1;
}

int main() {

    return 0;
}
