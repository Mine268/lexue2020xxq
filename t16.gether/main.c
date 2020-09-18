#include <stdio.h>
#include <stdlib.h>

#define LEN 500 // 500000
#define ABS(x) ((x>=0)?x:-x)
#define DIS(x,y,x0,y0) (ABS(x-x0)+ABS(y-y0))

int cmp(const void *, const void *);

int main(void)
{
    int T, n;
    long long pos1[LEN], pos2[LEN], pos1_c[LEN], pos2_c[LEN];
    scanf("%d", &T);
    for (int k = 0; k < T; k++)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%lld%lld", &pos1[i], &pos2[i]);
            pos1_c[i] = pos1[i]; pos2_c[i] = pos2[i];
        }
        qsort(pos1_c, n, sizeof(long long int), cmp);
        qsort(pos2_c, n, sizeof(long long int), cmp);
        int half = n / 2;
        long long c1 = pos1_c[half], c2 = pos2_c[half];
        unsigned long long res = 0;
        printf("Case: %d\n", k + 1);
        for (int i = 0; i < n; i++)
        {
            res += DIS(c1, c2, pos1[i], pos2[i]);
            printf("%llu.0000\n", res);
        }
    }
    getchar(); getchar();
    return 0;
}

int cmp(const void *p1, const void *p2)
{
    if (*(long long*)p1 - *(long long*)p2 >= 0) return 1;
    return -1;
}
