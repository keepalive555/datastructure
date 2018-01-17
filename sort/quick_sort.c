#include <stdio.h>
#include <stdlib.h>

// 快速排序实现
// 快速排序时间复杂度证明：https://www.cnblogs.com/surgewong/p/3381438.html

void quick_sort(int *arr, int low, int high) {
    if(low >= high) {
        return ;
    }
    int pivot = arr[low]; // 标准
    while(low < high) {
        // 自右向左扫描
        while(low < high && arr[high] >= pivot) {
            high--;
        }
    }
}
