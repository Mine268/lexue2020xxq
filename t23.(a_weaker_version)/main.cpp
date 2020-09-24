#include <iostream>
#include <vector>
using namespace std;

vector<long long> edge[200];
long long num, sizeTree[200];
long long ans;

long long dfs(long long i, long long f);

int main(void)
{
    cin >> num;
    long long a, b;
    for (int i = 0; i < num; i++)
    {
        cin >> a >> b;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    dfs(a, -1);
    cout << ans;
    getchar();
    getchar();
    return 0;
}

long long dfs(long long i, long long f)
{
    for (int j = 0; j < edge[i].size(); j++)
    {
        long long tmp = edge[i][j];
        if (tmp != f) sizeTree[i] += dfs(tmp, i);
    }
    ans += (num + 1 - sizeTree[i]) * sizeTree[i];
    sizeTree[i] += 1;
    return sizeTree[i];
}