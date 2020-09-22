#include <iostream>
#include <climits>
using namespace std;

typedef struct _NODE
{
    int val;
    struct _NODE *next;
} NODE;
typedef NODE* PNODE;

#define LEN 101 // 1000001
PNODE nextArr[LEN] = {0}; // 表示第i个节点可以指向的节点

// 把数字val加入到next的第i个链表中
void addto(int val, int i);
// 把第i位上的值为val的节点删除
void delat(int val, int i);

int main(void) {
    addto(2, 1);
    addto(3, 1);
    addto(4, 1);
    delat(2, 1);
    return 0;
}

void delat(int val, int i) // RE
{
    PNODE head = nextArr[i], pre;
    if (head->val == val) {
        if (head->next == NULL) {
            nextArr[i] == NULL;
            free(head);
        } else {
            nextArr[i] = head->next;
            free(head);
        }
    } else {
        while (head->val != val) {
            pre = head;
            head = head->next;
        }
        pre->next = head->next;
        free(head);
    }
    return;
}

void addto(int val, int i)
{
    PNODE *head = &nextArr[i];
    PNODE tmp = (PNODE)malloc(sizeof(NODE));
    tmp->val = val;
    tmp->next = NULL;
    if (*head == NULL) *head = tmp;
    else
    {
        while ((*head)->next != NULL) head = &(*head)->next;
        (*head)->next = tmp;
    }
    return;
}
