#include <iostream>
#include <cstdio>
const int INF = 0x7fffffff;
int main()
{
    int n;
    scanf("%d", &n);
    int ans = 1;
    double x, maxNumber = -INF;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lf", &x);
        if (x > maxNumber)
        {
            maxNumber = x;
            ans = i;
        }
    }
    printf("position = %d, maxNumber = %lf", ans, maxNumber);
    return 0;
}