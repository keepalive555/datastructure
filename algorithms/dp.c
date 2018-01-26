#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 0x7fffffff

// 动态规划解决钱币问题

void dp() {
    int value = 11;
    int coins[] = {1, 3, 5};
    int coins_number = sizeof(coins) / sizeof(int);
    int *min = (int *)malloc(sizeof(int)*(value+1));
    if(!min) {
        return ;
    }
    min[0] = 0;
    int i, j;
    for(i=1; i<(value+1); i++) {
        min[i] = MAX;
    }
    for(i=1; i<=value; i++) {
        // 首轮求d(1)的值
        for(j=0; j<coins_number; j++) {
            if(coins[j] <= i && (min[i-coins[j]] + 1 < min[i])) {
                min[i] = min[i-coins[j]]+1;
            }
        }
        printf("d{%d)=%d\n", i, min[i]);
    }
    free((void *)min);
}

int main() {
    dp();
}
