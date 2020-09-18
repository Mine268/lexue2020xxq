#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define LEN 500 // 500000
#define ABS(x) (((x)>=0)?(x):-(x))
#define DIS(x,y,x0,y0) (ABS((x)-(x0))+ABS((y)-(y0)))

int cmp(const void *, const void *);
void putnumber(unsigned long long int);
long long pos1[LEN], pos2[LEN], pos1_c[LEN], pos2_c[LEN];

int main(void)
{
    int T, n;
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

        int half = n >> 1;
        long long c1 = pos1_c[half], c2 = pos2_c[half];
        unsigned long long res = 0;
        printf("Case: %d\n", k + 1);
        if (n && 1 == 1)
            for (int i = 0; i < n; i++)
            {
                res += DIS(c1, c2, pos1[i], pos2[i]);
                printf("%llu.0000\n", res);
            }
        else
        {
            c1 = (pos1_c[half] + pos1_c[half - 1]) * 5; c2 = (pos2_c[half] + pos2_c[half - 1]) * 5;
            for (int i = 0; i < n; i++)
            {
                res += DIS(c1, c2, pos1[i] * 10, pos2[i] * 10);
                putnumber(res); putchar('\n');
            }
        }
        
    }
    getchar(); getchar();
    return 0;
}

void putnumber(unsigned long long int num)
{
    char tmp[100] = {0};
    sprintf(tmp, "%llu", num);
    int len = strlen(tmp);
    for (int i = 0; i < len; i++)
        if (i != len - 1) putchar(tmp[i]);
        else if (tmp[i] == '5') printf(".5000");
        else printf(".0000");
}

int cmp(const void *p1, const void *p2)
{
    if (*(long long*)p1 - *(long long*)p2 > 0) return 1;
    return -1;
}

/*
1
8
0 0
0 4
2 2
3 -1
1 -3
-2 -3
-4 -1
-2 2

1
6
100 200
0 0
0 0
0 0
0 0
0 0
*/