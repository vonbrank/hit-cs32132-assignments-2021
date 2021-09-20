#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;
const int maxn = 100500;
const int maxm = 500500;
inline int intRangeRand()
{
    static int seed = time(NULL);
    return seed = int(seed * 48271LL % 2147483647);
}
inline int getNextRandInt()
{
    return intRangeRand();
}
inline int getNextRandInt(int n)
{
    return intRangeRand() % n + 1;
}
inline int getNextRandInt(int a, int b)
{
    if(a > b) swap(a, b);
    return a + intRangeRand() % (b - a + 1);
}
int topoSequeue[maxn];
bool vis[maxn];
int main()
{
    int n = 8;
    printf("输入图的点数：\n");
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
    {
        int x;
        while (true)
        {
            x = getNextRandInt(n);
            if(!vis[x]) break;
        }
        vis[x] = true;
        topoSequeue[i] = x;
        
    }
    for(int i=1; i<n; i++)
    {
        int u = topoSequeue[i];
        int numberOfTo = getNextRandInt(n/2);
        for(int j=1; j<=n; j++) vis[j] = false;
        for(int j=1; j<=numberOfTo; j++)
        {
            int toIndex = getNextRandInt(i+1, n);
            int v = topoSequeue[toIndex];
            if(!vis[v]) printf("%d %d\n", u, v);
            vis[v] = true;
        }
    }
    return 0;
}