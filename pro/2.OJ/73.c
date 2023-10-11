/*************************************************************************
	> File Name: 73.c
	> Author: 
	> Mail: 
	> Created Time: Fri 15 Jul 2022 10:07:38 AM CST
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>

typedef struct UnionSet {
    int *father;
    int size;
}UnionSet;

UnionSet *initSet(int n) {
    UnionSet *u = (UnionSet *)malloc(sizeof(UnionSet));
    u->father = (int *)malloc(sizeof(int) * n);
    u->size = n + 1;

    int i;
    for(i = 0; i < u->size; i++) {
        u->father[i] = i;
    }
    return u;
}

void freeSet(UnionSet *u) {
    if(!u) return ;
    free(u->father);
    free(u);
    return ;
}

int find(UnionSet *u, int idx) {
/*
    if(u->father[idx] == idx) return idx;
    return find(u, u->father[idx]);
*/
    return u->father[idx] = u->father[idx] == idx ? idx : find(u, u->father[idx]);
}

int merge(UnionSet *u, int a, int b) {
    int fa = find(u, a), fb = find(u, b);
    if(fa == fb) return 0;
    u->father[fa] = fb;
    return 1;
}

int m = 0;
int idx(int i, int j) {
    return i * m + j + 1;
}

int main() {
    int n, m, i, j;
    scanf("%d %d", &n, &m);
    char (*arr)[m + 5] = malloc(sizeof(char) * (n + 5) * (m + 5));
    for(i = 0; i < n; i++) {
        scanf("%s", arr[i]);
    }
    UnionSet *u = initSet(m * n + 5);
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            if(arr[i][j] == 'X') continue;
            if(j > 0 && arr[i][j - 1] == 'O') {
                merge(u, idx(i, j), idx(i, j - 1));
            }
            if(i > 0 && arr[i - 1][j] == 'O') {
                merge(u, idx(i - 1, j), idx(i , j));    
            }
            if(i == 0 || i == n - 1) {
                merge(u, idx(i, j), 0);
            }
            if(j == 0 || j == m - 1) {
                merge(u, idx(i, j), 0);
            }
        }
    }
    int sum = 0;
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            if(arr[i][j] == 'X') continue;
            sum += find(u, idx(i, j)) != find(u, 0);
        }
    }
    printf("%d\n", sum);
    free(arr);
    return 0;
}
