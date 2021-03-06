#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <limits.h>

#define LEN          500 // 250000
#define RIGHT(x)     (2*(x)+2)
#define LEFT(x)      (2*(x)+1)
#define PARENT(x)    ((((x)+1)>>1)-1)
#define MAX          0x7F7F7F7F // 2,139,062,143
#define MIN          0x80808080 // -2,139,062,144

typedef struct HEAP
{
    int data[LEN]; // 这个堆的数据
    int size;  // 这个对当下的大小
    int capicity; // 这个堆的最大容量
} heap;

// 以下是堆的相关操作，包括堆最大堆和最小堆的操作

// 给堆数组进行初始化为MIN(最大堆)、MAX(最小堆)，容量为num，最大堆为1最小堆为-1
void iniHeap(heap*, int, int);
// 最大堆的增添操作
void maxHeapPush(heap*, int);
// 最大堆的弹出操作
int maxHeapPop(heap*);
// 最小堆的增添操作
void minHeapPush(heap*, int);
// 最小堆的弹出操作
int minHeapPop(heap*);
// 释放堆
void delHeap(heap*);
// 输出堆数组，用于调试
void printHeap(heap *);

// 以下是用于运算的最大堆

// 小于x的数组成的最大堆
heap lessX_maxH;
// 大于x的数组成的最小堆
heap greatX_minH;
// 小于y的数组成的最大堆
heap lessY_maxH;
// 大于y的数组成的最小堆
heap greatY_minH;

int main(void)
{
    // int arr[10] = {6,4,2,7,8,9,1,0,5,12};
    // heap mH; iniHeap(&mH, 10, -1);
    // for (int i = 0; i < 10; i++)
    // {
    //     minHeapPush(&mH, arr[i]);
    //     printHeap(&mH);
    // }
    // for (int i = 0; i < 10; i++)
    // {
    //     printf("[%d] ", minHeapPop(&mH));
    //     printHeap(&mH);
    // }
    // getchar();
    // return 0;

    int T; scanf("%d", &T); getchar();
    for (int i = 0; i < T; i++)
    {
        int n; scanf("%d", &n); getchar();
        // next表示下一个要读入的数字
        // mid表示当下两个维度分别的中位数
        int nextX, nextY, midX = MIN, midY = MIN;
        int leftX = 0, rightX = 0, leftY = 0, rightY = 0;
        long long res = 0;
        // 每次读入n组坐标之前需要初始化堆
        iniHeap(&lessX_maxH, LEN, 1); iniHeap(&lessY_maxH, LEN, 1);
        iniHeap(&greatX_minH, LEN, -1); iniHeap(&greatY_minH, LEN, -1);

        scanf("%d%d", &nextX, &nextY);
        printf("Case: %d\n0.0000\n", i + 1);
        midX = nextX; midY = nextY;
        while (n-- > 1)
        {
            scanf("%d%d", &nextX, &nextY); getchar();

            // 调整x维度的曼哈顿距离
            if (leftX == rightX)
            {
                // 左右堆规模相同，输入小于或等于中位数
                if (nextX <= midX)
                {
                    res += midX - nextX;
                    maxHeapPush(&lessX_maxH, nextX);
                }
                // 左右堆规模相同，输入大于中位数
                else
                {
                    minHeapPush(&greatX_minH, nextX);
                    int tmp = minHeapPop(&greatX_minH);
                    maxHeapPush(&lessX_maxH, midX);
                    res += nextX - midX;
                    midX = tmp;
                }
                leftX++;
            }
            else // 这是leftX = rightX + 1的情况
            {
                // 左堆比右堆大一，输入大于或等于中位数
                if (nextX >= midX)
                {
                    res += nextX - midX;
                    minHeapPush(&greatX_minH, nextX);
                }
                // 左堆比右堆大一，输入小于中位数
                else
                {
                    maxHeapPush(&lessX_maxH, nextX);
                    int tmp = maxHeapPop(&lessX_maxH);
                    minHeapPush(&greatX_minH, midX);
                    midX = tmp;
                    res += midX - nextX;
                }
                rightX++;
            }

            // 调整y维度的曼哈顿距离
            if (leftY == rightY)
            {
                if (nextY <= midY)
                {
                    res += midY - nextY;
                    maxHeapPush(&lessY_maxH, nextY);
                }
                else
                {
                    minHeapPush(&greatY_minH, nextY);
                    int tmp = minHeapPop(&greatY_minH);
                    maxHeapPush(&lessY_maxH, midY);
                    res += nextY - midY;
                    midY = tmp;
                }
                leftY++;
            }
            else
            {
                if (nextY >= midY)
                {
                    res += nextY - midY;
                    minHeapPush(&greatY_minH, nextY);
                }
                else
                {
                    maxHeapPush(&lessY_maxH, nextY);
                    int tmp = maxHeapPop(&lessY_maxH);
                    minHeapPush(&greatY_minH, midY);
                    midY = tmp;
                    res += midY - nextY;
                }
                rightY++;
            }
            printf("%d.0000\n", res);
        }

        // 每次使用完成之后需要清空堆
        // delHeap(&lessX_maxH); delHeap(&lessY_maxH);
        // delHeap(&greatX_minH); delHeap(&greatY_minH);
    }

    getchar();
    return 0;
}

void printHeap(heap *h)
{
    for (int i = 0; i < h->size + 1; i++) printf("%d ", h->data[i]);
    putchar('\n');
    return;
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

    int ind = h->size;
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
    return MAX;
    else
    {
        int res = h->data[0], ind = 0;
        h->size--;
        h->data[0] = h->data[h->size];
        h->data[h->size] = MAX;
        while (h->data[ind] > h->data[LEFT(ind)] || h->data[ind] > h->data[RIGHT(ind)])
        {
            int choice, tmp;
            if (h->data[LEFT(ind)] > h->data[RIGHT(ind)]) choice = RIGHT(ind);
            else choice = LEFT(ind);
            tmp = h->data[ind];
            h->data[ind] = h->data[choice];
            h->data[choice] = tmp;
        }
        return res;
    }
}

void maxHeapPush(heap *h, int val)
{
    if (h->size == h->capicity) return;

    int ind = h->size;
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
    return MIN;
    else
    {
        int res = h->data[0], ind = 0;
        h->size--;
        h->data[0] = h->data[h->size];
        h->data[h->size] = MIN;
        while (h->data[ind] < h->data[LEFT(ind)] || h->data[ind] < h->data[RIGHT(ind)])
        {
            int choice, tmp;
            if (h->data[LEFT(ind)] < h->data[RIGHT(ind)]) choice = RIGHT(ind);
            else choice = LEFT(ind);
            tmp = h->data[ind];
            h->data[ind] = h->data[choice];
            h->data[choice] = tmp;
        }
        return res;
    }
}

void iniHeap(heap * h, int num, int sel)
{
    h->size = 0;
    h->capicity = num;
    memset(h->data, sel == 1 ? 0x80 : 0x7F, sizeof(h->data));
    return;
}
