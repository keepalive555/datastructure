#include <stdio.h>
#include <stdlib.h>


int binary_search(int *arr, int n, int key) {
    // 参数arr是int数组，n代表数据元素数
    int low = 0, high = n - 1;
    int mid = 0;
    while(low <= high) {
        mid = (low + high) / 2;
#ifndef NDEBUG
        printf("low=%d, high=%d, mid=%d.\n", low, high, mid);
#endif
        if(key == arr[mid]) {
            return mid;
        } else if(key < arr[mid]) {
            // 继续搜索左半区间
            high = mid - 1;
        } else {
            // 继续搜索右边区间
            low = mid + 1;
        }
    }
    return -1;
}


int main() {
    int a[] = {1, 3, 4, 6, 7, 9, 10, 12, 15, 19};
    int n = sizeof(a) / sizeof(int);
#ifndef NDEBUG
    printf("elements number: %d\n", n);
#endif
    printf("binary search: %d\n", binary_search(a, n, 9));
}
