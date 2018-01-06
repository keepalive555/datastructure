#include <stdio.h>
#include <stdlib.h>

// 选择排序
// 从剩余n-i-1个元素中选出最小的元素，然后做交换
// 选择排序性能稍微优于冒泡排序
// 时间复杂度为O(n^2)

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


void select_sort(Sequence *seq) {
    int i, j, min;
    for(i=0; i<seq->length; i++) {
        min = i;
        for(j=i+1; j<seq->length; j++) {
            if(seq->array[j] < seq->array[min]) {
                min = j;
            }
        }
        if(i!=min) {
            swap(&seq->array[i], &seq->array[min]);
        }
    }
}

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

    select_sort(&seq);

    int i;
    for(i=0; i<seq.length; i++) {
        printf("value of element(%2d) = %d\n", i, seq.array[i]);
    }
}
