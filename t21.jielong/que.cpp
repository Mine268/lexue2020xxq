#include <iostream>
using namespace std;

// 队列元素
typedef struct _NUM_NODE {
    int val;
    struct _NUM_NODE* next;
} NNODE;
typedef NNODE* PNNODE;

/* 队列使用的头尾指针 */
PNNODE pstart = NULL;
PNNODE pend = NULL;

/* 以下是队列操作 */
void pushnum(int);
int popnum();
bool empty();

// 队列方法，是否为空
bool empty()
{
    if (pstart == NULL && pend == NULL) return true;
    else return false;
}

// 队列方法，压入元素
void pushnum(int val) {
    PNNODE tmp = (PNNODE)malloc(sizeof(NNODE));
    tmp->val = val;
    tmp->next = NULL;
    if (pstart == NULL && pend == NULL) {
        pstart = tmp;
        pend = tmp;
    } else {
        pend->next = tmp;
        pend = tmp;
    }
    return;
}

// 队列方法，弹出元素
int popnum() {
    if (pstart == NULL && pend == NULL) return -1;
    int res = pstart->val;
    if (pstart == pend) {
        free(pstart);
        pstart = NULL;
        pend = NULL;
    } else {
        PNNODE tmp = pstart;
        pstart = pstart->next;
        free(tmp);
    }
    return res;
}