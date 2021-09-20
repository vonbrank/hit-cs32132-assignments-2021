#include <stdio.h>
#include <stdlib.h>

#define N 20

void del(int match[][N], int i, int n)
{
    for (int j = 0; j < n; j++)
    {
        match[j][i] = 0;
    }
}

void sort(int match[][N], int n, int ans[])
{
    int count = 1; //判断已经找了几个
    int read[n];   //标记是否已被找到过
    for (int i = 0; i < n; i++)
    {
        read[i] = 0; //初始化为0
    }
    for (int k = 0; k < n; k++) //一共找n次
    {
        for (int i = 0; i < n; i++) //每次遍历n个选手
        {
            int judge = 1; //标记该选手是否是要找的元素
            for (int j = 0; j < n; j++)
            {
                if (match[i][j] == 1)
                {
                    judge = 0; //但凡有一个1，就不是要找的元素
                }
            }
            if (judge == 1) //找到出度为0的点
            {
                if (read[i] == 1) //如果这个点已经被找过
                    continue;
                else
                {
                    read[i] = 1;            //标记该点，说明已被找到过
                    ans[n - count] = i + 1; //从末位开始存
                    del(match, i, n);       //在邻接矩阵中删除该点
                    count++;
                    break;
                }
            }
        }
    }
}

int main()
{
    printf("多少选手？\n");
    int n;
    scanf("%d", &n);
    int match[N][N];
    for (int i = 0; i < n; i++)
    {
        printf("请输入第%d位选手的赛况（与第i位选手比赛时获胜就在第i位上输入1，否则输入0，与自己的场次输入0。用空格间隔）：\n", i + 1);
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &match[i][j]);
        }
    }
    /*int test[4][4] = {0,1,1,1,0,0,1,1,0,0,0,0,0,0,1,0};
    for(int p = 0; p < n; p++)
    {
        for(int q = 0; q < n; q++)
        {
            printf("%d ",test[p][q]);
        }
        printf("\n");
    }
    */

    /*for(int p = 0; p < n; p++)
    {
        for(int q = 0; q < n; q++)
        {
            printf("%d ",match[p][q]);
        }
        printf("\n");
    }*/

    int ans[n];
    for (int i = 0; i < n; i++)
    {
        ans[i] = 0;
    }
    sort(match, n, ans);
    for (int i = 0; i < n; i++)
    {
        printf("%d", ans[i]);
    }
    return 0;
}

/*
4
0 1 1 1
0 0 1 1
0 0 0 0
0 0 1 0

*/