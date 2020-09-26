#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

#define N 300 // 300000

queue<int> bfsline;
vector<int> edge[N];
int flag;

void bfs(int h, int r);

int main(void)
{
    int n, m, ans = 0;
    cin >> n >> m;
    while (m-- > 0)
    {
        ans++;
        int a, b;
        cin >> a >> b;
        edge[a].push_back(b);

        bfs(b, a);
        if (flag == 1) break;
    }
    if (flag == 1) cout << ans << endl;
    else cout << -1 << endl;

    return 0;
}

void bfs(int h, int r)
{
    bfsline.push(h);
    while (bfsline.empty() == false)
    {
        int t = bfsline.front();
        bfsline.pop();
        for (auto n : edge[t])
        {
            if (n != r) bfsline.push(n);
            else
            {
                flag = 1;
                return;
            }
        }
    }
    return;
}
