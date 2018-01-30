// 利用动态规划解决最长上升子序列
#include <stdio.h>
#include <stdlib.h>


int lis(int *arr, int n) {
    int *d = (int *)malloc(sizeof(int) * n);
    if(!d) {
        return -1;
    }
    free((void *)d);
    int len = 1;
    int i, j;
    for(i=0; i<n; i++) {
        d[i] = 1;
        for(j=0; j<i; j++) {
            if(arr[j] <= arr[i] && (d[j]+1 > d[i])) {
                d[i] = d[j]+1;
            }
        }
        len = d[i] > len ? d[i] : len;
    }
    return len;
}

int main() {
    int arr[] = {2, 7, 1, 5, 6, 4, 3, 8, 9};
    printf("lis: %d\n", lis(arr, sizeof(arr)/sizeof(int)));
    return 0;
}
