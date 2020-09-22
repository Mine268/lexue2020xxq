#include <iostream>
#include <climits>
using namespace std;

typedef struct _NODE
{
    int val;
    struct _NODE *next;
} NODE;
typedef NODE* PNODE;
// 队列元素
typedef struct _NUM_NODE {
    int val;
    struct _NUM_NODE* next;
} NNODE;
typedef NNODE* PNNODE;

#define LEN 101 // 1000001
PNODE nextArr[LEN] = {0}; // 表示第i个节点可以指向的节点
/* 队列使用的头尾指针 */
PNNODE pstart = NULL;
PNNODE pend = NULL;

// 把数字val加入到next的第i个链表中
void addto(int val, int i);
// 把第i位上的值为val的节点删除
void delat(int val, int i);
/* 以下是队列操作 */
void pushnum(int);
int popnum();
bool empty();

int main(void)
{
    int m, flag = 0, tmp_count; scanf("%d", &m); getchar();
    long long step = 0, ans = -1;
    while (m-- > 0)
    {
        int from, to;
        scanf("%d %*d %*d %d", &from, &to);
        addto(to, from);
    }
    int w1_from, w1_end, w2_from, w2_end;
    int w12, w13, w22, w23;
    scanf("%d%d%d%d %d%d%d%d", &w1_from, &w12, &w13, &w1_end, &w2_from, &w22, &w23, &w2_end);
    if (w1_from == w2_from && w12 == w22 && w13 == w23 && w1_end == w2_end)
    {
        cout << "1" << endl;
        return 0;
    } else if (w1_end == w2_from) {
        cout << "2" << endl;
        return 0;
    }
    delat(w1_end, w1_from);
    delat(w2_end, w2_from);

    pushnum(w1_end);
    tmp_count = 1;
    while (empty() == false)
    {
        int addcount = 0;
        while (tmp_count-- > 0)
        {
            int curl = popnum();
            PNODE pcurl = nextArr[curl];
            while (pcurl != NULL)
            {
                pushnum(pcurl->val);
                addcount++;
                if (pcurl->val == w2_from) flag = 1;
                pcurl = pcurl->next;
            }
            nextArr[curl] = NULL;
        }
        step++;
        if (flag)
        {
            ans = step;
            break;
        }
        tmp_count = addcount;
    }

    if (flag == 0) cout << "-1" << endl;
    else cout << ans + 2 << endl;

    return 0;
}

void delat(int val, int i)
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

/*
8
1 0 0 4
4 0 0 7
7 0 0 9
9 0 0 2
2 0 0 8
8 0 0 10
4 0 0 1
1 0 0 8
1 0 0 4
8 0 0 10

7
1 0 0 3
3 0 0 4
4 0 0 1
10 0 0 3
1 0 0 7
7 0 0 8
8 0 0 9

5
1 0 0 3
3 0 0 4
4 0 0 4
4 0 0 7
7 0 0 8
1 0 0 3
7 0 0 8

7
1 0 0 3
3 0 0 7
7 0 0 4
4 0 0 4
4 0 0 8
8 0 0 8
8 0 0 7
1 0 0 3
8 0 0 8
*/