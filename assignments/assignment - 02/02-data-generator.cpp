#include <iostream>
#include <cstdio>
#include <ctime>

class Random
{
public:
    static int randInt()
    {
        static int seed = time(NULL);
        return seed = int(seed * 48271LL % 2147483647);
    }
    static int randInt(int n)
    {
        return randInt() % (n + 1);
    }
    static int randInt(int a, int b)
    {
        return a + randInt() % (b - a + 1);
    }
};

int main()
{
    int n, m, maxn;
    printf("输入三个整数n, m, maxn，分别表示A, B集合的元素个数及其最大值。\n");
    scanf("%d %d %d", &n, &m, &maxn);
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", Random::randInt(maxn));
    }
    printf("\n");
    for (int i = 1; i <= m; i++)
    {
        printf("%d ", Random::randInt(maxn));
    }
    printf("\n");
    return 0;
}