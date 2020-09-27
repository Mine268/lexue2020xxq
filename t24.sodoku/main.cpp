#include <iostream>
using namespace std;

char mat[17][17];
char tmp[5][5]; // 用于旋转
int change[5][5];

void turn(int n, int m); // 旋转n行m列的方阵

int main(void)
{
    int T;
    cin >> T; getchar();
    while (T-- > 0)
    {
        for (int i = 1; i <= 16; i++)
        {
            for (int j = 1; j <= 16; j++) mat[i][j] = getchar();
            getchar();
        }
        turn(2,3);
    }
    return 0;
}

void turn(int n, int m)
{
    for (int k = 1; k <= 4; k++)
        for (int i = 1; i <= 4; i++)
            tmp[5 - i][k] = mat[k + 4 * (n - 1)][4 * (m - 1) + i];
}
