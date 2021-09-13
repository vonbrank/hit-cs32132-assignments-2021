#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;
const int maxn = 1050;
const int maxm = 1000500;

inline int intRangeRand()
{
    static int seed = time(NULL);
    return seed = int(seed * 48271LL % 2147483647);
}
struct Edge
{
    int to, w, next;
} G[maxm];
int n, cnt;
int head[maxn], ans[maxn];
bool vis[maxn];
void addEdge(int u, int v, int w)
{
    cnt++;
    G[cnt].to = v;
    G[cnt].w = w;
    G[cnt].next = head[u];
    head[u] = cnt;
}

void dfs(int u, int depth, bool &flag)
{
    ans[depth] = u;
    if (depth == n)
    {
        flag = true;
        return;
    }
    vis[u] = true;
    for (int i = head[u]; i; i = G[i].next)
    {
        int v = G[i].to;
        if (vis[v])
            continue;
        dfs(v, depth + 1, flag);
        if (flag)
            return;
    }
    vis[u] = false;
}

int main()
{
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            int u, v, w = 1;
            scanf("%d %d", &u, &v);
            addEdge(u, v, w);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            vis[j] = false;
        }
        bool flag = false;
        dfs(i, 1, flag);
        if (flag)
            break;
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", ans[i]);
    }
    return 0;
}