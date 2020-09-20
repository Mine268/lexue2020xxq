#include <stdio.h>
#include <limits.h>

#define N 500 // 500001
#define ABS(x,y) (((x)>(y))?((x)-(y)):((y)-(x)))

long long x_big[N] = {0}, xb = 0, x_small[N] = {0}, xs = 0;
long long y_big[N] = {0}, yb = 0, y_small[N] = {0}, ys = 0;

/* 一切数组操作从1开始考虑，size表示堆中的数组的数量 */
void insrtBig(long long arr[], long long val, long long* size); // 向最大堆数组arr中插入值val，size用于告知插入位置
void insrtSml(long long arr[], long long val, long long* size);
long long popBig(long long arr[], long long* size); // 从最大堆弹出数值，size用于告知此时的数组规模
long long popSml(long long arr[], long long* size);
void printH(long long arr[], long long* size); // 输出数组，debug用

int main(void)
{
    long long T, n, midX, midY, nextX, nextY;
    long long res;
    scanf("%lld", &T);
    for (long long i = 1; i <= T; i++)
    {
        res = 0; xb = xs = yb = ys = 0;
        scanf("%lld", &n);
        scanf("%lld%lld", &midX, &midY); getchar();
        printf("Case: %lld\n0.0000\n", i);
        for (long long j = 2; j <= n; j++)
        {
            scanf("%lld%lld", &nextX, &nextY);
            if (nextX > midX) insrtSml(x_big, nextX, &xb);
            else insrtBig(x_small, nextX, &xs);
            if (nextY > midY) insrtSml(y_big, nextY, &yb);
            else insrtBig(y_small, nextY, &ys);

            res += ABS(nextX, midX) + ABS(nextY, midY);
            if (ABS(xs, xb) >= 2)
            {
                if (xb > xs)
                {
                    int judge = x_big[1] - midX;
                    insrtBig(x_small, midX, &xs);
                    midX = popSml(x_big, &xb);
                    res -= judge;
                }
                else
                {
                    int judge = midX - x_small[1];
                    insrtSml(x_big, midX, &xb);
                    midX = popBig(x_small, &xs);
                    res -= judge;
                }
            }
            if (ABS(ys, yb) >= 2)
            {
                if (yb > ys)
                {
                    int judge = y_big[1] - midY;
                    insrtBig(y_small, midY, &ys);
                    midY = popSml(y_big, &yb);
                    res -= judge;
                }
                else
                {
                    int judge = midY - y_small[1];
                    insrtSml(y_big, midY, &yb);
                    midY = popBig(y_small, &ys);
                    res -= judge;
                }
            }
            printf("%lld.0000\n", res);
        }
    }
    getchar(); getchar();
    return 0;
}

void printH(long long *arr, long long* size)
{
    for (long long i = 1; i <= *size; i++) printf("%lld ", arr[i]);
    putchar('\n');
    return;
}

long long popSml(long long arr[], long long *size)
{
    if (*size == 0) return INT_MIN;
    else
    {
        long long ind = 1, res = arr[ind];
        arr[ind] = arr[*size];
        while (2 * ind < *size)
        {
            long long left = ind * 2, right = 2 * ind + 1;
            if (right > *size || arr[left] < arr[right])
                if (arr[ind] > arr[left])
                {
                    arr[ind] = arr[left] ^ arr[ind];
                    arr[left] = arr[left] ^ arr[ind];
                    arr[ind] = arr[left] ^ arr[ind];
                    ind = left;
                }
                else break;
            else
                if (arr[right] < arr[ind])
                {
                    arr[right] = arr[right] ^ arr[ind];
                    arr[ind] = arr[right] ^ arr[ind];
                    arr[right] = arr[right] ^ arr[ind];
                    ind = right;
                }
                else break;
        }
        *size -= 1;
        return res;
    }
}

long long popBig(long long arr[], long long *size)
{
    if (*size == 0) return INT_MIN;
    else
    {
        long long ind = 1, res = arr[ind];
        arr[ind] = arr[*size];
        while (2 * ind < *size)
        {
            int left = ind * 2, right = 2 * ind + 1;
            if (right > *size || arr[left] > arr[right])
                if (arr[ind] < arr[left])
                {
                    arr[ind] = arr[left] ^ arr[ind];
                    arr[left] = arr[left] ^ arr[ind];
                    arr[ind] = arr[left] ^ arr[ind];
                    ind = left;
                }
                else break;
            else
                if (arr[right] > arr[ind])
                {
                    arr[right] = arr[right] ^ arr[ind];
                    arr[ind] = arr[right] ^ arr[ind];
                    arr[right] = arr[right] ^ arr[ind];
                    ind = right;
                }
                else break;
        }
        *size -= 1;
        return res;
    }
}

void insrtBig(long long arr[], long long val, long long *size)
{
    *size += 1;
    arr[*size] = val;
    long long ind = *size;
    while (ind > 1 && arr[ind] > arr[ind >> 1])
    {
        arr[ind] = arr[ind >> 1] ^ arr[ind];
        arr[ind >> 1] = arr[ind >> 1] ^ arr[ind];
        arr[ind] = arr[ind >> 1] ^ arr[ind];
        ind >>= 1;
    }
    return;
}

void insrtSml(long long arr[], long long val, long long *size)
{
    *size += 1;
    arr[*size] = val;
    long long ind = *size;
    while (ind > 1 && arr[ind] < arr[ind >> 1])
    {
        arr[ind] = arr[ind >> 1] ^ arr[ind];
        arr[ind >> 1] = arr[ind >> 1] ^ arr[ind];
        arr[ind] = arr[ind >> 1] ^ arr[ind];
        ind >>= 1;
    }
    return;
}