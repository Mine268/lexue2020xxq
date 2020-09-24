#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

typedef struct _posN {
    int i;
    int j;
} POS;

#define M 100
#define N 100
#define K 50

char mat[N][M];
long long mark[N][M]; // false:无 true:有
int vis[N][M][K];
queue<POS> bfsline;

// 快速构建点对
POS consPos(int i, int j);
// 判断点是否合法
bool isValid(int i, int j, int m, int n);

int main(void) {
    int T; cin >> T;
    while (T-- > 0) {
        memset(mark, 0, sizeof(long long) * N * M);
        memset(vis, 0, sizeof(int) * N * M * K);
        while (bfsline.empty() == false) bfsline.pop();
        int m, n, k, si, sj, ei, ej, pathcount = 0, intervalDot = 0;
        long long step = 0;
        cin >> n >> m >> k;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> mat[i][j];
                mark[i][j] = false;
                if (mat[i][j] == '.') pathcount += k; // 统计点的数量，在时空维度上
                if (mat[i][j] == 'S') {
                    si = i;
                    sj = j;
                    mat[i][j] = '.';
                }
                if (mat[i][j] == 'E') {
                    ei = i;
                    ej = j;
                    mat[i][j] = '.';
                }
            }
        }

        int tmp_count = 1, flag = 0;

        bfsline.push(consPos(si, sj));
        mark[si][sj] = step;
        vis[si][sj][0] = 1;
        while (1) {
            step++;
            int add_count = 0;
            while (tmp_count-- > 0) {
                POS tmp = bfsline.front(); bfsline.pop();
                if (isValid(tmp.i, tmp.j - 1, m, n) && mark[tmp.i][tmp.j - 1] != step &&
                    (mat[tmp.i][tmp.j - 1] == '.' || (mat[tmp.i][tmp.j - 1] == '*' && step % k == 0))) {
                        mark[tmp.i][tmp.j - 1] = step;
                        bfsline.push(consPos(tmp.i, tmp.j - 1));
                        add_count++;

                        if (tmp.i == ei && tmp.j - 1 == ej) flag = 1;
                        else if (mat[tmp.i][tmp.j - 1] == '.') {
                            if (vis[tmp.i][tmp.j - 1][step % k] == 1) intervalDot++;
                            vis[tmp.i][tmp.j - 1][step % k]++;
                        }
                }
                if (isValid(tmp.i, tmp.j + 1, m, n) && mark[tmp.i][tmp.j + 1] != step &&
                    (mat[tmp.i][tmp.j + 1] == '.' || (mat[tmp.i][tmp.j + 1] == '*' && step % k == 0))) {
                        mark[tmp.i][tmp.j + 1] = step;
                        bfsline.push(consPos(tmp.i, tmp.j + 1));
                        add_count++;
                        
                        if (tmp.i == ei && tmp.j + 1 == ej) flag = 1;
                        else if (mat[tmp.i][tmp.j + 1] == '.') {
                            if (vis[tmp.i][tmp.j + 1][step % k] == 1) intervalDot++;
                            vis[tmp.i][tmp.j + 1][step % k]++;
                        }
                }
                if (isValid(tmp.i + 1, tmp.j, m, n) && mark[tmp.i + 1][tmp.j] != step &&
                    (mat[tmp.i + 1][tmp.j] == '.' || (mat[tmp.i + 1][tmp.j] == '*' && step % k == 0))) {
                        mark[tmp.i + 1][tmp.j] = step;
                        bfsline.push(consPos(tmp.i + 1, tmp.j));
                        add_count++;
                        
                        if (tmp.i + 1 == ei && tmp.j == ej) flag = 1;
                        else if (mat[tmp.i + 1][tmp.j] == '.') {
                            if (vis[tmp.i + 1][tmp.j][step % k] == 1) intervalDot++;
                            vis[tmp.i + 1][tmp.j][step % k]++;
                        }
                }
                if (isValid(tmp.i - 1, tmp.j, m, n) && mark[tmp.i - 1][tmp.j] != step &&
                    (mat[tmp.i - 1][tmp.j] == '.' || (mat[tmp.i - 1][tmp.j] == '*' && step % k == 0))) {
                        mark[tmp.i - 1][tmp.j] = step;
                        bfsline.push(consPos(tmp.i - 1, tmp.j));
                        add_count++;
                        
                        if (tmp.i - 1 == ei && tmp.j == ej) flag = 1;
                        else if (mat[tmp.i - 1][tmp.j] == '.') {
                            if (vis[tmp.i - 1][tmp.j][step % k] == 1) intervalDot++;
                            vis[tmp.i - 1][tmp.j][step % k]++;
                        }
                }
            }
            tmp_count = add_count;
            if (flag == 1) {
                cout << step << endl;
                break;
            } else if (intervalDot == pathcount) {
                cout << "-1" << endl;
                break;
            }
        }
    }
    return 0;
}

bool isValid(int i, int j, int m, int n) {
    if (i >= 0 && i < m && j >= 0 && j < n) return true;
    else return false;
}

POS consPos(int i, int j) {
    return {i, j};
}
