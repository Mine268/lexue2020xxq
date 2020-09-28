#include <iostream>
using namespace std;

#define VMAX 20 // 2001
#define PMAX 100 // 100001
#define MAX(x,y) (((x)>(y))?(x):(y))

unsigned long long dp[VMAX][PMAX];

int main(void)
{
    int cap, n, w[100], v[100], dp[2][100];
    cin >> n >> cap;
    for (int i = 1; i <= n; i++)
    {
        cin >> w[i] >> v[i];
    }
    for (int i = 0; i <= cap; i++)
    {
        dp[0][i] = 0;
    }
    dp[1][0] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= cap; j++)
        {
            if (w[i] > j)
            {
                dp[i % 2][j] = dp[(i - 1) % 2][j];
            }
            else
            {
                dp[i % 2][j] = MAX(dp[(i - 1) % 2][j], dp[(i - 1) % 2][j - w[i]] + v[i]);
            }
        }
    }
    cout << dp[n % 2][cap] << endl;
    return 0;
}
