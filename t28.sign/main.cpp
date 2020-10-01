#include <iostream>
using namespace std;

#define MAX(x,y) (((x)>(y))?(x):(y))
#define MIN(x,y) (((x)<(y))?(x):(y))
#define N 200 // 2020
#define MD 2147483647
#define _for(i,a,b) for(int i=(a); i<(b); ++i)
#define _rep(i,a,b) for(int i=(a); i<=(b); ++i)

long dp[N][N];
long a[N];

int main(void)
{
    int n, firTail;
    cin >> n;
    cin >> firTail;
    dp[1][firTail] = 1;
    _rep(i, 1, n)
        scanf("%d", &a[i]);

    _rep(i, 2, n)
    {
        _rep(j, 1, N)
        {
            if (dp[i - 1][j] == 0)
                continue;
            else if (a[i] <= MIN(a[i - 1], j))
            {
                dp[i][MAX(a[i - 1], j)] += dp[i - 1][j];
                dp[i][MAX(a[i - 1], j)] %= MD;
            } else if (a[i] >= MAX(a[i - 1], j))
            {
                dp[i][MIN(a[i - 1], j)] += dp[i - 1][j];
                dp[i][MIN(a[i - 1], j)] %= MD;
            } else
            {
                dp[i][MIN(a[i - 1], j)] += dp[i - 1][j];
                dp[i][MAX(a[i - 1], j)] += dp[i - 1][j];
                dp[i][MAX(a[i - 1], j)] %= MD;
                dp[i][MIN(a[i - 1], j)] %= MD;
            }
        }
    }

    long long sum = 0;
    for (int i = 0; i <= N; ++i)
    {
        sum += dp[n][i];
        sum %= MD;
    }

    cout << sum << endl;

    return 0;
}
