#include <stdio.h>
#include <stdlib.h>

// 插入排序
// 拿生活中的插扑克牌为例

#define MAXSIZE 10

typedef struct _sequence {
    int array[MAXSIZE];
    int length;
} Sequence;


void print_sequence(Sequence *seq) {
    int i;
    printf("=======================\n");
    for(i=0; i<seq->length; i++) {
        printf("(i=%d, value=%d) ", i, seq->array[i]);
    }
    printf("\n=======================\n");
}


void insert_sort(Sequence *seq) {
    int i, j, k;
    // 分成两个子数组
    for(i=1; i<seq->length; i++) {
        // 如果右侧元素小于左侧元素
        if(seq->array[i] < seq->array[i-1]) {
            // 移动左边排序数组内的元素
            k = seq->array[i];
            for(j=i-1; seq->array[j]>k; j--) {
                seq->array[j+1] = seq->array[j];
            }
            seq->array[j+1] = k;
            print_sequence(seq);
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

    insert_sort(&seq);

    int i;
    for(i=0; i<seq.length; i++) {
        printf("value of element(%2d) = %d\n", i, seq.array[i]);
    }
}
