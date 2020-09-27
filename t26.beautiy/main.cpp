#include <iostream>
#include <limits.h>
using namespace std;
#define N 100 // 500000
#define MAX(x,y) (((x)>(y))?(x):(y))

long long byt[N], dp[4][N];

int main(void)
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        scanf("%lld", &byt[i]);
    dp[1][1] = byt[1];
    dp[2][2] = byt[2] + byt[1];
    dp[3][3] = byt[3] + byt[2] + byt[1];
    for (int i = 1; i <= 3; i++)
    {
        long long max = MAX(dp[i - 1][i], dp[i - 1][i - 1]);
        for (int j = i + 1; j <= n; j++)
        {
            dp[i][j] = MAX(max, dp[i][j - 1]) + byt[j];
            max = MAX(max, dp[i - 1][j]);
        }
    }

    long long ans = LLONG_MIN;
    for (int i = 3; i <= n; i++)
        ans = max(ans, dp[3][i]);
    
    cout << ans << endl;

    return 0;
}