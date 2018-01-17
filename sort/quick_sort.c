#include <stdio.h>
#include <stdlib.h>

// 快速排序实现
// 快速排序时间复杂度证明：https://www.cnblogs.com/surgewong/p/3381438.html

// 快速排序Python代码实现
/* def quick_sort(lists, left, right):
 *     # 快速排序
 *     if left >= right:
 *         return lists
 *     key = lists[left]  # 左侧
 *     low = left
 *     high = right
 *     while left < right:
 *         while left < right and lists[right] >= key:
 *             right -= 1
 *         lists[left] = lists[right]
 *         while left < right and lists[left] <= key:
 *             left += 1
 *         lists[right] = lists[left]
 *     lists[right] = key
 *     quick_sort(lists, low, left - 1)
 *     quick_sort(lists, left + 1, high)
 *     return lists */

void quick_sort(int *arr, int low, int high) {
    if(low >= high) {
        return ;
    }
    int i = low;
    int j = high;
    int pivot = arr[i]; // 标准
    while(i < j) {
        // 自右向左扫描
        while(i < j && arr[j] >= pivot) {
            j--;
        }
        arr[i] = arr[j];
        while(i < j && arr[i] <= pivot) {
            i++;
        }
        arr[j] = arr[i];
    }
    arr[j] = pivot;
    quick_sort(arr, low, i-1);
    quick_sort(arr, i+1, high); 
    return ;
}

int main(void) {
    int arr[] = {9, 5, 3, 8, 7, 6, 4, 1, 2, 0};
    int size = sizeof(arr) / sizeof(int);
    // 排序
    quick_sort(arr, 0, size-1);
    int i;
    for(i=0; i<size; i++) {
        printf("%d\n", i);
    }
}
