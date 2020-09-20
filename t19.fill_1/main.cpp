#include <iostream>
#include <stack>
#include <climits>
using namespace std;

int main(void)
{
    stack<int> lake;
    int n = 0, height = 0;
    do
    {
        if (scanf("%d", &n) == EOF) break;
        while (n-- > 0)
        {
            scanf("%d", &height);
            if (lake.empty() == true) lake.push(height);
            else
            {
                if ((lake.top() & 1) == (height & 1)) lake.pop();
                else lake.push(height);
            }
        }
        if (lake.empty() == true || lake.size() == 1) printf("YES\n");
        else printf("NO\n");
        while (lake.empty() == false) lake.pop();
    } while (true);

    return 0;
}