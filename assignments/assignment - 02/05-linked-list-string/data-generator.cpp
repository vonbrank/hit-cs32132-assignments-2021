#include <iostream>
#include <cstdio>
#include "Random.h"
using namespace std;
const int maxLen = 50;
const int maxn = 50;
int main()
{
    freopen("input.txt", "w", stdout);
    int len = Random::randInt(maxLen);
    int n = Random::randInt(1, maxn);
    int s[maxLen + 10];
    for (int i = 0; i < len; i++)
    {
        if (Random::randInt() % 2)
            printf("%c", s[i] = Random::randInt(25) + 'a');
        else
            printf("%c", s[i] = Random::randInt(25) + 'A');
    }
    printf("\n");
    printf("%d\n", n);
    for (int i = 1; i <= n; i++)
    {
        if (Random::randInt() % 2)
        {
            int a = Random::randInt(0, len - 1);
            int b = Random::randInt(a, len - 1);
            printf("1 ");
            if (Random::randInt(1, 100) <= 5)
            {
                printf("abc");
            }
            for (int j = a; j <= b; j++)
            {
                printf("%c", s[j]);
            }
            if (Random::randInt(1, 100) <= 5)
            {
                printf("abc");
            }
            printf("\n");
        }
        else
        {
            int a = Random::randInt(0, len - 1);
            int b = Random::randInt(a, len - 1);
            printf("2 %d %d\n", a, b);
        }
    }
    return 0;
}