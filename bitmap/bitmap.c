#include <stdio.h>

#define MAXSIZE 1024
#define SHIFT 5
#define MASK 0xffffffff
static unsigned int bitmap[MAXSIZE / (sizeof(unsigned int) * 8) + 1];


void set(int n) {
    // 置位操作
    bitmap[n >> SHIFT] |= 1 << (n & MASK);
}

void clr(int n) {
    // 复位操作
    bitmap[n >> SHIFT] &= ~(1 << (n & MASK));
}

int test(int n) {
    // 检测是否置位
    int i = n >> SHIFT;
    if(bitmap[i] & (1 << (n & MASK)))
      return 1;
    return 0;
}

int main(void) {
    int n = 1023;
    printf("space: %d\n", sizeof(bitmap) / sizeof(unsigned int));
    set(n);
    printf("has set flag: %d\n", test(n));
    clr(n);
    printf("has set flag: %d\n", test(n));
    set(n);
    printf("has set flag: %d\n", test(n));
    clr(n);
}
