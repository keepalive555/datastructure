#include <stdio.h>

 struct ListNode {
     int val;
     struct ListNode *next;
};

struct ListNode* reverseList(struct ListNode* head) {
    // 反转链表
    struct ListNode *reverse = NULL; // 逆序表头指针
    struct ListNode *next = NULL; // 指向链表下一个节点的指针
    struct ListNode *curr = head; // 指向链表表头
    while(curr != NULL) {
        next = curr->next;
        if(!reverse) {
            curr->next = NULL;
            reverse = curr;
        } else {
            curr->next = reverse;
            reverse = curr;
        }
        curr = next;
    }
    return reverse;
}
