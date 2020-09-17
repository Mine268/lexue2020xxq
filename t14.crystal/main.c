#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define LEN 100 // 100000
#define MIN(x, y, z) (((z) > (((x) > (y)) ? (y) : (x))) ? (((x) > (y)) ? (y) : (x)) : (z))

struct raw
{
    int a;
    int b;
    int c;
    int order;
} rawArr[LEN];

void written(int); // 按照升序排列a b c
int cmp(const void *, const void *); // a>b:1 a=b:0 a<b:-1

int main(void)
{
    int n;
    long long ai, aj, a0;
    long long ans1 = 0, ans2 = 0;
    scanf("%d", &n); getchar();
    for (int i = 0; i < n; i++)
    {
        written(i);
        if (rawArr[i].a > ans1)
        {
            ans1 = rawArr[i].a;
            a0 = rawArr[i].order + 1;
        }
    }
    qsort(rawArr, n, sizeof(struct raw), cmp);

    for (int i = n - 1; i > 0; i--)
        if (rawArr[i].c == rawArr[i - 1].c && rawArr[i].b == rawArr[i - 1].b)
        {
            int restriction = MIN(rawArr[i].c, rawArr[i].b, rawArr[i].a + rawArr[i - 1].a);
            if (restriction > ans2)
            {
                ans2 = restriction;
                ai = rawArr[i].order + 1; aj = rawArr[i - 1].order + 1;
            }
        }

    if (ans1 >= ans2) printf("%d\n%lld\n", 1, a0);
    else if (ai < aj) printf("%d\n%lld %lld\n", 2, ai, aj);
    else if (ai >= aj) printf("%d\n%lld %lld\n", 2, aj, ai);

    getchar(); getchar();
    return 0;
}

/*
6
1 2 3
4 1 1
4 2 3
4 2 3
4 3 3
5 5 5
*/

int cmp(const void *p1, const void *p2)
{
    struct raw a = *(struct raw *)p1, b = *(struct raw *)p2;
    if (a.c > b.c) return 1;
    else if (a.c < b.c) return -1;
    else if (a.c == b.c)
    {
        if (a.b > b.b) return 1;
        else if (a.b < b.b) return -1;
        else if (a.b == b.b)
        {
            if (a.a > b.a) return 1;
            else if (a.a < b.a) return -1;
            else return 0;
        }
    }
}

void written(int i)
{
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    if (a > b)
    {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }
    if (b > c)
    {
        b = b ^ c;
        c = b ^ c;
        b = b ^ c;
    }
    if (a > b)
    {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }
    rawArr[i].a = a;
    rawArr[i].b = b;
    rawArr[i].c = c;
    rawArr[i].order = i;

    return;
}
