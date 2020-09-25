#include <iostream>
#include <vector>
using namespace std;

#define N 200 // 2000000
#define HALF(x) (((x)&1) + ((x)>>1)) // 除二并向上取整

vector<int> edge[N];
/*
oddR 所有节点到根节点的奇数点的个数
evenR 所有节点到根节点的偶数点的个数
sizeTree 以r为根的数中每一个几点所代表的子树的节点个数
*/
int oddR, evenR, sizeTree[N];
int disRoot[N]; // 节点到根的距离
long long sum[N], sumUp;

int E(int i); // 到节点i的距离为偶数的点的个数
int O(int i); // 到节点i的距离为奇数的点的个数
int dfs1(int i, int f); // 给出所有点的子树的规模
void dfs2(int i, int f, int r, int depth); // 给出所有点的奇偶节点的数量
void dfs3(int i, int f); // 转移计算

int main(void)
{
    int n, a, b, r;
    cin >> n;
    while (n-- > 1)
    {
        scanf("%d%d", &a, &b); getchar();
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    r = a;
    dfs1(r, 0);
    dfs2(r, 0, r, 1);
    sumUp += sum[r];
    dfs3(r, 0);
    cout << sumUp / 2 << endl;
    return 0;
}

void dfs3(int i, int f)
{
    for (int j = 0; j < edge[i].size(); j++)
    {
        int tmp = edge[i][j];
        if (tmp != f)
        {
            sum[tmp] = sum[i] + E(i) - sizeTree[tmp] + 1;
            sumUp += sum[tmp];
            dfs3(tmp, i);
        }
    }
    return;
}

int E(int i) { return disRoot[i] % 2 == 0 ? evenR : oddR - 1; }
int O(int i) { return disRoot[i] % 2 == 0 ? oddR : evenR + 1; }

void dfs2(int i, int f, int r, int depth)
{
    for (int j = 0; j < edge[i].size(); j++)
    {
        int tmp = edge[i][j];
        if (tmp != f)
        {
            if (depth & 1 == 1) // 距离根节点奇数距离
                oddR++;
            else evenR++;  // 距离根节点偶数距离
            disRoot[tmp] = depth;
            sum[r] += HALF(depth);
            dfs2(tmp, i, r, depth + 1);
        }
    }
    return;
}

int dfs1(int i, int f)
{
    for (int j = 0; j < edge[i].size(); j++)
    {
        int tmp = edge[i][j];
        if (tmp != f)
            sizeTree[i] += dfs1(tmp, i);
    }
    sizeTree[i]++;
    return sizeTree[i];
}
