#include <iostream>
#include <queue>
#include <climits>
using namespace std;

#define LEN 500 // 500000

priority_queue<int, vector<int>, less<int>> minX; // 所有比x小的
priority_queue<int, vector<int>, greater<int>> maxX; // 所有比x大的
priority_queue<int, vector<int>, less<int>> minY; // 所有比y大的
priority_queue<int, vector<int>, greater<int>> maxY; // 多有比y小的

int main(void)
{
    int T = 0, n = 0;
    scanf("%d", &T);
    for (int i = 0; i < T; i++)
    {
        long long res = 0, midX = LLONG_MIN, midY = LLONG_MIN, nextX, nextY;
        int leftX = 0, rightX = 0, leftY = 0, rightY = 0;
        scanf("%d", &n);
        scanf("%lld%lld", &midX, &midY); printf("Case %d: 0.0000\n", i + 1);
        while (n-- > 1)
        {
            scanf("%lld%lld", &nextX, &nextY);
            if (leftX = rightX) // 调整第一个维度的曼哈顿距离
            {
                if (nextX <= midX)
                {
                    res += midX - nextX;
                    minX.push(nextX);
                }
                else
                {
                    res += nextX - midX;
                    maxX.push(nextX);
                    int tmp = maxX.top(); maxX.pop();
                    minX.push(midX);
                    midX = tmp;
                }
                leftX++;
            }
            else
            {
                if (nextX >= midX)
                {
                    res += nextX - midX;
                    maxX.push(nextX);
                }
                else
                {
                    res += midX - nextX;
                    minX.push(nextX);
                    int tmp = minX.top(); minX.pop();
                    maxX.push(midX);
                    midX = tmp;
                }
                rightX++;
            }

            if (leftY == rightY) // 调整第二个维度的曼哈顿距离
            {
                if (nextY <= midY)
                {
                    res += midY - nextY;
                    minY.push(nextY);
                }
                else
                {
                    res += nextY - midY;
                    maxY.push(nextY);
                    int tmp = maxY.top(); maxY.pop();
                    minY.push(midY);
                    midY = tmp;
                }
                leftY++;
            }
            else
            {
                if (nextY >= midY)
                {
                    res += nextY - midY;
                    maxY.push(nextY);
                }
                else
                {
                    res += midY - nextY;
                    minY.push(nextY);
                    int tmp = minY.top(); minY.pop();
                    maxY.push(midY);
                    midY = tmp;
                }
                rightY++;
            }

            printf("%lld.0000\n", res);
        }
    }

    getchar(); getchar();
    return 0;
}