#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

#define CLEN 100 // 1000000

typedef struct S_HOUSE
{
    int height;
    int color;
} HOUSE;

stack<struct S_HOUSE> line;
int color[CLEN];
HOUSE houses[CLEN];

int main(void)
{
    int T; scanf("%d", &T);
    while (T-- > 0)
    {
        int n; scanf("%d", &n);
        long long ans = 0;
        memset(color, 0, sizeof(color));
        while (line.empty() == false) line.pop();
        for (int i = 0; i < n; i++)
            scanf("%d", &houses[i].color);
        for (int i = 0; i < n; i++)
        {
            int h; scanf("%d", &h);
            houses[i].height = h;

            if (line.empty() == true)
            {
                color[houses[i].color]++;
                ans++;
                line.push(houses[i]);
            }
            else
            {
                if (houses[i].height < line.top().height)
                {
                    color[houses[i].color]++;
                    if (color[houses[i].color] == 1) ans++;
                    line.push(houses[i]);
                }
                else
                {
                    while (line.empty() == false && houses[i].height >= line.top().height)
                    {
                        int colortmp = line.top().color;
                        color[colortmp]--;
                        if (color[colortmp] == 0) ans--;
                        line.pop();
                    }
                    color[houses[i].color]++;
                    if (color[houses[i].color] == 1) ans++;
                    line.push(houses[i]);
                }
            }
            printf("%lld", ans);
            if (i != n - 1) putchar(' ');
            else putchar('\n');
        }
    }

    getchar(); getchar();
    return 0;
}