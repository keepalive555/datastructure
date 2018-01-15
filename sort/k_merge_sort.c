#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MINKEY 0x80000000
#define MAXKEY 0x7fffffff
#define CAP 1024

// 释放指针
#define SAFE_FREE(p) do { \
    if(p) { \
        free((void *)p); \
        p = NULL; \
    } \
}while(0)

// K路归并排序
typedef struct _losertree {
    int *ls;
    int *b;
    int k;
} LoserTree;

typedef struct _array {
    int arr[CAP];
    int size;
    int pos; // 当前位置
} Array;

// 函数声明
void adjust(LoserTree *ls, int i);

void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void print_sequence(int *arr, int size) {
    int i;
    printf("=======================\n");
    for(i=0; i<size; i++) {
        printf("(i=%d, value=%d) ", i, arr[i]);
    }
    printf("\n=======================\n");
}

LoserTree *create_losertree(int k) {
    // 创建败者树
    LoserTree *ls = (LoserTree *)malloc(sizeof(LoserTree));
    if(!ls) {
        return NULL;
    }
    ls->k = k;
    ls->b = (int *)malloc(sizeof(int) * (k+1));
    if(!ls->b) {
        SAFE_FREE(ls);
        return NULL;
    }
    ls->ls = (int *)malloc(sizeof(int) * k);
    if(!ls->ls) {
        SAFE_FREE(ls->b);
        SAFE_FREE(ls);
        return NULL;
    }
    // 初始化败者树
    int i;
    for(i=0; i<ls->k; i++) {
        ls->ls[i] = ls->k;
    }
    ls->b[ls->k] = MINKEY;
    // for(i=ls->k-1; i>=0; i--) {
    //     adjust(ls, i);
    // }
    // print_sequence(ls->b, ls->k+1);
    // print_sequence(ls->ls, ls->k);
    return ls;
}

void adjust(LoserTree *ls, int i) {
    // 从叶子节点b[i]到根节点的父节点ls[0]调整败者树
    int t = (i + ls->k) / 2;
    while(t > 0) {
        // ls->b[i] 叶子节点值
        // ls->b[ls->ls[t]] 父节点比较
        if(ls->b[i] > ls->b[ls->ls[t]]) {
            swap(&i, &ls->ls[t]);
        }
        t = t / 2;
    }
    ls->ls[0] = i;
}

int finished(Array *arrays, int k) {
    int finished = 1;
    int i;
    for(i=0; i<k; i++) {
        if(arrays[i].pos < arrays[i].size) {
            finished = 0;
            break;
        }
    }
    return finished;
}

void k_merge(Array *arrays, int k) {
    printf("k merge sorting...\n");
    // k路归并排序
    LoserTree *ls = create_losertree(k);
    if(!ls) {
        return ;
    }
    int i;
    for(i=0; i<ls->k; i++) {
        ls->b[i] = arrays[i].arr[arrays[i].pos++];
    }
    for(i=0; i<ls->k; i++) {
        adjust(ls, i);
    }
    print_sequence(ls->b, ls->k+1);
    print_sequence(ls->ls, ls->k);
    int p;
    while(!finished(arrays, k)) {
        p = ls->ls[0];
        printf(">>%2d(%2d)=%2d\n", p, arrays[p].pos, ls->b[p]);

        if(arrays[p].pos < arrays[p].size) {
            ls->b[p] = arrays[p].arr[++arrays[p].pos];
        } else {
            ls->b[p] = MAXKEY;
        }
        adjust(ls, p);
        sleep(1);
    }
}

int main(void) {
    int init_arr[5][12] = {
         {11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33},
         {10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32},
         {41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63},
         {40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62},
         {70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81},
    };
    Array arrs[5];
    memset((void *)arrs, 0, sizeof(arrs));
    // 初始化数组
    int i, j;
    for(i=0; i<5; i++) {
        arrs[i].size = 12;
        arrs[i].pos = 0;
        for(j=0; j<12; j++) {
            arrs[i].arr[j] = init_arr[i][j];
        }
    }
    k_merge(arrs, 5);
}
