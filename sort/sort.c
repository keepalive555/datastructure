#include <stdio.h>
#include <stdlib.h>

// 冒泡排序

#define MAXSIZE 10

typedef struct _sequence {
    int array[MAXSIZE];
    int length;
} Sequence;


void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void bubble_sort(Sequence *seq) {
    int i, j;
    for(i=0; i<seq->length; i++) {
        for(j=i+1; j<seq->length; j++) {
            if(seq->array[i] > seq->array[j]) {
                swap(&seq->array[i], &seq->array[j]);
            }
        }
    }
}

// 冒泡排序复杂度分析
// O() = 1 + 2 + 3 + ... + (n - 1)
// O(n^2) = (n - 1) * n / 2 = (n*n - n) / 2


int main(void) {
    Sequence seq;
    seq.length = 10;
    seq.array[0] = 3;
    seq.array[1] = 9;
    seq.array[2] = 8;
    seq.array[3] = 1;
    seq.array[4] = 2;
    seq.array[5] = 4;
    seq.array[6] = 5;
    seq.array[7] = 6;
    seq.array[8] = 7;
    seq.array[9] = 0;

    bubble_sort(&seq);

    int i;
    for(i=0; i<seq.length; i++) {
        printf("value of element(%2d) = %d\n", i, seq.array[i]);
    }
}
