#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define LEN 500 // 500000
#define RIGHT(x) (2*(x)+2)
#define LEFT(x) (2*(x)+1)
#define PARENT(x) (((x)+1)>>1-1)

typedef struct HEAP
{
    int *data; // 这个堆的数据
    int size;  // 这个对当下的大小
    int capicity; // 这个堆的最大容量
} heap;

void iniHeap(heap*, int, int); // 给堆数组进行初始化为INT_MIN，容量为num，最大堆为1最小堆为-1
void maxHeapPush(heap*, int); // 最大堆的增添操作
int maxHeapPop(heap*); // 最大堆的弹出操作
void minHeapPush(heap*, int); // 最小堆的增添操作
int minHeapPop(heap*); // 最小堆的弹出操作
void delHeap(heap*); // 释放堆

int main(void)
{
    return 0;
}

void delHeap(heap *h)
{
    free(h->data);
    h->size = 0;
    h->capicity = 0;
    return;
}

void minHeapPush(heap *h, int val)
{
    if (h->size == h->capicity) return;

    int ind;
    for (ind = h->size; h->data[ind] != INT_MAX; ind--);
    h->data[ind] = val;
    while (ind != 0 && h->data[ind] < h->data[PARENT(ind)])
    {
        int tmp = h->data[ind];
        h->data[ind] = h->data[PARENT(ind)];
        h->data[PARENT(ind)] = tmp;
        ind = PARENT(ind);
    }
    h->size++;
    return;
}

int minHeapPop(heap* h)
{
    if (h->size == 0)
    return INT_MAX;
    else
    {
        int res = h->data[0];
        int ind = 0;
        while (h->data[LEFT(ind)] != INT_MAX || h->data[RIGHT(ind)] != INT_MAX)
        {
            int choice;
            if (h->data[LEFT(ind)] <= h->data[RIGHT(ind)]) choice = LEFT(ind);
            else choice = RIGHT(ind);
            h->data[ind] = h->data[choice];
            ind = choice;
        }
        h->data[ind] = INT_MAX;
        h->size--;
        return res;
    }
}

void maxHeapPush(heap *h, int val)
{
    if (h->size == h->capicity) return;

    int ind;
    for (ind = h->size; h->data[ind] != INT_MIN; ind--);
    h->data[ind] = val;
    while (ind != 0 && h->data[ind] > h->data[PARENT(ind)])
    {
        int tmp = h->data[ind];
        h->data[ind] = h->data[PARENT(ind)];
        h->data[PARENT(ind)] = tmp;
        ind = PARENT(ind);
    }
    h->size++;
    return;
}

int maxHeapPop(heap* h)
{
    if (h->size == 0)
    return INT_MIN;
    else
    {
        int res = h->data[0];
        int ind = 0;
        while (h->data[LEFT(ind)] != INT_MIN || h->data[RIGHT(ind)] != INT_MIN)
        {
            int choice;
            if (h->data[LEFT(ind)] >= h->data[RIGHT(ind)]) choice = LEFT(ind);
            else choice = RIGHT(ind);
            h->data[ind] = h->data[choice];
            ind = choice;
        }
        h->data[ind] = INT_MIN;
        h->size--;
        return res;
    }
}

void iniHeap(heap * h, int num, int sel)
{
    h->data = (int *)malloc(sizeof(int) * num);
    memset(h->data, (sel == 0) ? INT_MAX : INT_MIN, sizeof(int) * num);
    h->size = 0;
    h->capicity = num;
    return;
}