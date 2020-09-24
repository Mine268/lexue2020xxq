#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <iostream>
#include <queue>
using namespace std;

typedef struct _pos
{
    int i;
    int j;
} POS; // 用于保存bfs过程中的坐标与队列中

#define M 102
#define N 102
#define K 51
char mat[N][M][K];
int vis[N][M][K];
queue<POS> bfsline;

// 判断点是否在局内
bool valid(int i, int j, int m, int n);
// 快速构建坐标结构体
POS *constructPos(int i, int j);
POS makepair(int i, int j);

int main(void)
{
    int T;
    scanf("%d", &T);
    getchar();
    while (T-- > 0)
    {
        /* mat无需进行初始化 */
        memset(vis, 0, sizeof(int) * M * N * K);
        int n, m, k, si, sj, ei, ej; // n为行，m为列
        long long step = 0, ans;
        scanf("%d%d%d", &n, &m, &k);
        getchar();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                char tmp;
                scanf("%c", &tmp);
                switch (tmp)
                {
                case '.':
                    for (int n = 0; n < k; n++)
                        mat[i][j][n] = '.';
                    break;
                case '#':
                    for (int n = 0; n < k; n++)
                        mat[i][j][n] = '#';
                    break;
                case 'S':
                    for (int n = 0; n < k; n++)
                        mat[i][j][n] = '.';
                    si = i;
                    sj = j;
                    break;
                case 'E':
                    for (int n = 0; n < k; n++)
                        mat[i][j][n] = '.';
                    ei = i;
                    ej = j;
                    break;
                case '*':
                    for (int n = 0; n < k; n++)
                        mat[i][j][n] = '*';
                    mat[i][j][k - 1] = '.';
                    break;
                }
            }
            getchar();
        }

        // 分层图搜索法
        int flag = 0; // 表示是否搜索到了目标
        bfsline.push(makepair(si, sj));
        vis[si][sj][0] = 1;
        int tmp_count = 1, add_count = 0;
        while (bfsline.empty() == false)
        {
            add_count = 0;
            step++;
            while (tmp_count-- > 0)
            {
                POS tmp = bfsline.front();
                bfsline.pop();
                // 左
                if (valid(tmp.i, tmp.j - 1, m, n) && mat[tmp.i][tmp.j - 1][step % k] == '.' && vis[tmp.i][tmp.j - 1][step % k] == 0)
                {
                    vis[tmp.i][tmp.j - 1][step % k] = 1;
                    bfsline.push(makepair(tmp.i, tmp.j - 1));
                    add_count++;
                    if (tmp.i == ei && tmp.j - 1 == ej && flag == 0)
                    {
                        flag = 1;
                        ans = step;
                    }
                }
                // 右
                if (valid(tmp.i, tmp.j + 1, m, n) && mat[tmp.i][tmp.j + 1][step % k] == '.' && vis[tmp.i][tmp.j + 1][step % k] == 0)
                {
                    vis[tmp.i][tmp.j + 1][step % k] = 1;
                    bfsline.push(makepair(tmp.i, tmp.j + 1));
                    add_count++;
                    if (tmp.i == ei && tmp.j + 1 == ej && flag == 0)
                    {
                        flag = 1;
                        ans = step;
                    }
                }
                // 上
                if (valid(tmp.i - 1, tmp.j, m, n) && mat[tmp.i - 1][tmp.j][step % k] == '.' && vis[tmp.i - 1][tmp.j][step % k] == 0)
                {
                    vis[tmp.i - 1][tmp.j][step % k] = 1;
                    bfsline.push(makepair(tmp.i - 1, tmp.j));
                    add_count++;
                    if (tmp.i - 1 == ei && tmp.j == ej && flag == 0)
                    {
                        flag = 1;
                        ans = step;
                    }
                }
                // 下
                if (valid(tmp.i + 1, tmp.j, m, n) && mat[tmp.i + 1][tmp.j][step % k] == '.' && vis[tmp.i + 1][tmp.j][step % k] == 0)
                {
                    vis[tmp.i + 1][tmp.j][step % k] = 1;
                    bfsline.push(makepair(tmp.i + 1, tmp.j));
                    add_count++;
                    if (tmp.i + 1 == ei && tmp.j == ej && flag == 0)
                    {
                        flag = 1;
                        ans = step;
                    }
                }
            }
            tmp_count = add_count;
        }
        if (flag == 1) cout << ans << endl;
        else cout << -1 << endl;
    }

    return 0;
}

/*
1
6 6 2
...S..
...#..
.#....
...#.#
...*..
..*E*.
7
*/

POS makepair(int i, int j)
{
    return {i, j};
}

POS *constructPos(int i, int j)
{
    POS *tmp = (POS *)malloc(sizeof(POS));
    tmp->i = i;
    tmp->j = j;
    return tmp;
}

bool valid(int i, int j, int m, int n)
{
    if (i >= 0 && i < m && j >= 0 && j < m)
        return true;
    else
        return false;
}
