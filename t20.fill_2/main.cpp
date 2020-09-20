#include <iostream>
#include <climits>
#include <stack>
using namespace std;

int main(void)
{
    stack<int> lake;
    int n = 0, height = 0, flag = 1, max = INT_MIN;
    do
    {
        if (scanf("%d", &n) == EOF) break;
        while (n-- > 0)
        {
            scanf("%d", &height);
            max = (max < height) ? height : max;
            if (lake.empty() == true) lake.push(height);
            else
            {
                if (lake.top() < height) flag = 0;
                else if (lake.top() > height) lake.push(height);
                else if (lake.top() == height) lake.pop();
            }
        }

        if (flag == 0) printf("NO\n");
        else
        {
            int count = lake.size();
            if (count > 1) printf("NO\n");
            else if (count == 1 && lake.top() != max) printf("NO\n");
            else printf("YES\n");
        }

        max = INT_MIN;
        flag = 1;
        while (lake.empty() == false) lake.pop();
    } while (true);
    getchar();
    return 0;
}