/*************************************************************************
	> File Name: 265.c
	> Author: 
	> Mail: 
	> Created Time: Tue 12 Jul 2022 02:00:25 PM CST
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct Stack {
    Node *head;
} Stack;

Node *initNode(int idx) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->val = idx;
    n->next = NULL;
    return n;
}

void freeNode(Node *p) {
    p ? free(p) : 0;
    return ;
}

Stack *initStack() {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->head = NULL;
    return s;
}

void freeStack(Stack *s) {
    if(!s) return ;
    Node *p = s->head, *k;
    while(p) {
        k = p;
        p = p->next;
        freeNode(k);
    }
    free(s);
    return ;
}

int push(Stack *s, int idx) {
    if(!s) return 0;
    Node *n = initNode(idx);
    n->next = s->head;
    s->head = n;
    return 1;
}

int isEmpty(Stack *s) {
    return !s && !s->head;
}

int pop(Stack *s) {
    Node *k = s->head;
    int tmp = k->val;
    s->head = k->next;
    freeNode(k);
    return tmp;
}

int top(Stack *s) {
    return s->head->val;
}

int main() {
    char str1[10005];
    char *str = str1 + 1;
    scanf("%s", str);
    str[-1] = 'X';
    Stack *s = initStack();
    push(s, -1);
    int i;
    int len = 0;
    for(i = 0; i < strlen(str); ++i) {
        char c = str[i];
        char t = str[top(s)];
        if((t == '(' && c == ')') || (t == '[' && c == ']') || (t == '{' && c == '}')) {
            pop(s);
            len = max(i - top(s), len);
        }else {
            push(s, i);
        }
    } 
    printf("%d\n", len);
    freeStack(s);
    return 0;
}
