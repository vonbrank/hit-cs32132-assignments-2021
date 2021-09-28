#include <iostream>
#include <cstdio>
#include "Random.h"
const int maxn = 10;
const int maxm = 50;
const int maxNum = 128;
int main()
{
    freopen("input.txt", "w", stdout);
    int n = Random::randInt(2, maxn);
    int m = Random::randInt(10, maxm);
    int k = m;
    printf("%d %d %d\n", n, m, k);
    for (int i = 1; i <= k; i++)
    {
        int p = Random::randInt(1, 100);
        if (p <= 60)
        {
            int x, y;
            x = Random::randInt(n - 1);
            y = Random::randInt(maxNum);
            printf("1 %d %d\n", x, y);
        }
        else if (p <= 90)
        {
            int x = Random::randInt(n - 1);
            printf("2 %d\n", x);
        }
        else
        {
            int x = Random::randInt(n - 1);
            printf("3 %d\n", x);
        }
    }
    return 0;
}