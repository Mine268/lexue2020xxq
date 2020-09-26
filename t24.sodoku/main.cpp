#include <iostream>
using namespace std;

char mat[17][17];

int main(void)
{
    int T;
    cin >> T;
    while (T-- > 0)
    {
        for (int i = 1; i <= 16; i++)
        {
            for (int j = 1; j <= 16; j++) scanf("%c", mat[i][j]);
            getchar();
        }
    }
    return 0;
}