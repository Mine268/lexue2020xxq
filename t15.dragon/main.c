#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define N 200 // 200000
/*
6
14 2
7 -6
3 7
10 -2
20 6
28 -14
13

4
0 1
1 1
5 -2
2 -1
3
*/
struct dragon
{
    int hardness;
    int exp;
} positive[N], negative[N];
int pcomp(const void*, const void*);
int ncomp(const void*, const void*);
int main(void)
{
    // pi, qi是数组positive和negative的游标
    long long n, pi = 0, ni = 0, A = 0;
    unsigned long long cost = 0;
    scanf("%lld", &n); getchar();
    struct dragon tmp;
    for (long long i = 0; i < n; i++)
    {
        scanf("%d%d", &tmp.hardness, &tmp.exp);
        if (tmp.exp >= 0) memcpy(&positive[pi++], &tmp, sizeof(struct dragon));
        else memcpy(&negative[ni++], &tmp, sizeof(struct dragon));
    }
    qsort(positive, pi, sizeof(struct dragon), pcomp);
    qsort(negative, ni, sizeof(struct dragon), ncomp);
    for (long long i = 0; i < pi; i++)
        if (A >= positive[i].hardness) A += positive[i].exp;
        else
        {
            cost += positive[i].hardness - A;
            A = positive[i].hardness + positive[i].exp;
        }
    for (long long i = 0; i < ni; i++)
        if (A >= negative[i].hardness) A += negative[i].exp;
        else
        {
            cost += negative[i].hardness - A;
            A = negative[i].hardness + negative[i].exp;
        }
    printf("%llu\n", cost);
    getchar(); getchar();
    return 0;
}
int ncomp(const void *p1, const void *p2)
{
    int key1 = ((struct dragon*)p1)->hardness + ((struct dragon*)p1)->exp; // x+y for the minimun attack after attack the dragon with negative exp. use greedy alg
    int key2 = ((struct dragon*)p2)->hardness + ((struct dragon*)p2)->exp;
    return -(key1 - key2);
}
int pcomp(const void *p1, const void *p2)
{
    int key1 = ((struct dragon*)p1)->hardness;
    int key2 = ((struct dragon*)p2)->hardness;
    return key1 - key2;
}