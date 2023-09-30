/*************************************************************************
	> File Name: 284.c
	> Author: 
	> Mail: 
	> Created Time: Thu 14 Jul 2022 06:42:20 PM CST
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>

#define swap(a,b) { \
    _typeof(a) _tmp=a; \
    a=b;b=_tmp; \
}

typedef struct Heap{
    int *data;
    int len;
    int size;
} Heap;

Heap *initHeap(int n) {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->data = (int *)malloc(sizeof(int) * n);
    h->len = 0;
    h->size = n;
    return h;
}

void freeHeap(Heap *h) {
    if(!h) {
        return ;
    }
    free(h->data);
    free(h);
    return ;
}

int push(Heap *h, int val) {
    if(!h) return 0;
    if(h->len == h->size) return 0;
    h->data[h->len] = val;
    int idx = h->len;
    while(idx && h->data[idx] > h->data[(idx - 1) / 2]) {
        //向上调整
        swap(h->data[idx], h->data[(idx - 1) / 2]);
        idx = (idx - 1) / 2;
    }
    h->len++;
    return 1;
}

int isEmpty(Heap *h) {
    return !h || !h->len;
}

void downadj(int *arr, int idx, int len) {
    while(2 * idx + 1 < len) {
        int tmp = idx, l = 2 * idx + 1, r = 2 * idx + 2;
        if(arr[l] > arr[tmp]) tmp = l;
        if(r < len && arr[r] > arr[tmp]) tmp = r;
        if(tmp == idx) break;
        swap(arr[tmp], arr[idx]);
        idx = tmp;
    }
    return ;
}

int pop(Heap *h) {
    int ret = h->data[0];
    h->data[0] = h->data[h->len - 1];
    h->len--;
    //向下调整
    downadj(h->data, 0, h->len);
    return ret;
}

typedef struct Goods {
    int d;
    int p;
} Goods;

void quick2sort(Goods *arr, int l, int r) {
    while(l < r) {
        int x = l, y = r, z = arr[(l + r) / 2].d;
        do{
            while(arr[x].d < z) {
                x++;
            }
            while(arr[y].d > z) {
                y--;
            }
            if(x <= y) {
                swap(arr[x], arr[y]);
                x++;
                y--;
            }
        }while(x <= y);
        quick2sort(arr, l, y);
        l = x;
    }
    return ;
}

int main() {
    int n;
    scanf("%d", &n);
    Goods *g = (Goods *)malloc(sizeof(Goods) * n);
    int i;
    for(i = 0; i < n; i++) {
        scanf("%d %d", &g[i].p, &g[i].d);
    }
    quick2sort(g, 0, n - 1);
    Heap *h = initHeap(n);
    int cnt = g[n - 1].d;
    i = n - 1;
    int sum = 0;
    while(cnt) {
        while(i > -1 && g[i].d == cnt) {
            push(h, g[i].p);
            i--;
        }
        if(!isEmpty(h)) sum += pop(h);
        cnt--;
    }
    printf("%d", sum);
    free(g);
    free(h);
    return 0;
}
