#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <queue>
using namespace std;

queue<string> qu;

int main(void)
{
    int n = 0;
    string cmd; // 命令与参数
    scanf("%d", &n);
    while (n-- > 0)
    {
        cmd.clear();
        cin >> cmd;
        if (cmd.compare(0, 6, "Arrive") == 0)
        {
            cin >> cmd;
            qu.push(cmd);
        }
        else if (cmd.compare(0, 5, "Leave") == 0 && qu.empty() == false) qu.pop();
        else if (cmd.compare(0, 6, "QueueH") == 0)
        {
            if (qu.empty() == true) printf("Empty queue\n");
            else cout << qu.front() << endl;
        }
        else if (cmd.compare(0, 6, "QueueT") == 0)
        {
            if (qu.empty() == true) printf("Empty queue\n");
            else cout << qu.back() << endl;
        }
    }
    return 0;
}