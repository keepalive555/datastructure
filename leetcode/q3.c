#include <stdio.h>
#include <stdlib.h>

int lengthOfLongestSubstring(char* s) {
    // 测试用例：abcabcbb
    int max = 0;
    int len = 0;
    char ch;
    char *f;
    while(f = s, (ch = *s) != '\0') {
        while(*++f != ch && *f != '\0') {}
        len = 0;
        s++;
    }
    return max;
}

int main() {
    char *s = "abcabcbb";
    printf("ret: %d\n", lengthOfLongestSubstring(s));
}
