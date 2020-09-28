#include <iostream>
#include <cstring>
using namespace std;

#define VM 100 // 2003
#define MN 10000000

long long dp[2][VM], w[2001];

int main(void)
{
    int n, V;
    long long sum = 0, ans = 0;
    cin >> n >> V;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &w[i]);
        sum += w[i];
    }

    memset(dp, 0, sizeof(long long) * 2 * VM);
    dp[0][0] = 1; dp[1][0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (long long j = 1; j <= sum; j++)
        {
            if (w[i] > j)
            {
                dp[i % 2][j] = dp[(i - 1) % 2][j] % MN;
            }
            else
            {
                dp[i % 2][j] = ((dp[(i - 1) % 2][j] % MN) + (dp[(i - 1) % 2][j - w[i]] % MN)) % MN;
            }
        }
    }

    for (int i = 1; i * V <= sum; i++)
        ans = (ans + dp[n % 2][i * V]) % MN;

    cout << ans << endl;

    return 0;
}
