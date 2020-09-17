#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define LEN 300 // 30000
struct task{
    int s;
    int f;
} t[LEN];

int cmp(void *, void *);

int main(void)
{
    int n, ans = 1;
    scanf("%d", &n); getchar();
    for (int i = 0; i < n; i++) scanf("%d%d", &t[i].s, &t[i].f);
    qsort(t, n, sizeof(struct task), cmp);

    int k = 0;
    for (int i = 1; i < n; i++)
        if (t[i].s >= t[k].f)
        {
            k = i;
            ans++;
        }

    printf("%d\n", ans);
    getchar(); getchar();

    return 0;
}

int cmp(void *p1, void *p2)
{
    return ((struct task*)p1)->f - ((struct task*)p2)->f;
}