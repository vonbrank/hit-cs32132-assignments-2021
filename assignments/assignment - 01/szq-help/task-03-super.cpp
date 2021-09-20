#include <iostream>
#include <cstdio>
const int maxn = 1050;

int n, m;
int G[maxn][maxn];
int now[maxn];
bool vis[maxn];
void dfs(int u, int length)
{
    vis[u] = true;
    now[length] = u;
    if (length == n)
    {
        for (int i = 1; i <= length; i++)
            printf("%d ", now[i]);
        printf("\n");
        exit(0);
    }
    for (int i = 1; i <= n; i++)
    {
        if (G[u][i] == 0 || vis[i])
            continue;
        dfs(i, length + 1);
    }
    vis[u] = false;
}

int main()
{
    printf("请输入一个整数 n ，表示队伍数目。\n");
    scanf("%d", &n);
    printf("请输入 n * (n - 1) / 2 行数据，每行两个数 i, j ，表示 i 胜过 j。\n");
    printf("请务必输入合法的比赛图。\n");
    m = n * (n - 1) / 2;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u][v] = 1;
    }
    printf("\n所求序列为：\n");
    for (int i = 1; i <= n; i++)
    {
        dfs(i, 1);
    }
    return 0;
}

/*
示例测试数据：

6
1 2
1 3
1 4
5 1
6 1
3 2
2 4
5 2
2 6
4 3
3 5
6 3
5 4
4 6
6 5

*/