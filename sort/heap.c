#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// 完全二叉树
// 二叉堆的实现
// 最小堆与最大堆

#define MAXSIZE 1024
#define PARENT(i) ((i-1)/2)
#define LEFT(i) (2*i+1)
#define RIGHT(i) (2*i+2)

// 举个例子：9, 8, 6, 7, 5, 1, 4, 2, 3
// 下标从0开始的话，下标范围：0~8
// 数组9个元素
// 中间元素小标mid = length / 2 = floor(9 / 2) = 4
// 中间元素做孩子left = 2 * mid + 1 = 9
// 最右一个有子节点的节点为：floor(length / 2) - 1

void swap(int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void heap_adjust(int *arr, int length, int i) {
    // 将数组i节点的子树调整为最大堆
    int tmp = arr[i];
    int child = LEFT(i); // 左孩子节点

    while(child < length) {
        // sleep(1);
        // 如果存在右节点并且右节点的值大于左节点，则指向右节点
        if(child+1 < length && arr[child] < arr[child+1]) {
            child++;
        }
        // 如果父节点值大于等于两个孩子节点，则退出
        if(tmp >= arr[child]) {
            break;
        }
        // 否则交换两个节点的值
        swap(&arr[i], &arr[child]);
        // 继续平衡子树
        i= child;
        tmp = arr[i];
        child = LEFT(i);
    }
}

void heap_sort(int *arr, int length) {
    // 利用最大堆进行排序
    // 将数组初始化为大顶堆
    int i, j;
    for(i=length/2-1; i>=0; i--) {
        printf("adjust loop i=%d\n", i);
        heap_adjust(arr, length, i);
    }
    // 堆排序
    for(j=length-1; j>=0;) {
        // 交换堆顶元素和末尾元素
        swap(&arr[0], &arr[j--]);
        // 重新平衡堆
        heap_adjust(arr, j, 0);
    }
}

void print_sequence(int *arr, int size) {
    int i;
    printf("=======================\n");
    for(i=0; i<size; i++) {
        printf("(i=%d, value=%d) ", i, arr[i]);
    }
    printf("\n=======================\n");
}

int main(void) {
    int arr[] = {3, 4, 5, 9, 7, 8, 1, 2, 0, 6};
    int size = sizeof(arr) / sizeof(int);
    heap_sort(arr, size);
    print_sequence(arr, size);
}
