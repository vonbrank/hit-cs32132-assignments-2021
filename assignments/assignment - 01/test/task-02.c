#include <stdio.h>
const int INF = 0x7fffffff;
int main()
{
    int n;
    scanf("%d", &n);
    int ans = 1, maxNumber = -INF, x;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        if (x > maxNumber)
        {
            x = maxNumber;
            ans = i;
        }
    }
    printf("%d", ans);
    return 0;
}