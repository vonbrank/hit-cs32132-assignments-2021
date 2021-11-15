/**************************************************************************

Author: 120L021403

Date: 2021-10-27

Description: HIT-数据结构与算法2021-4.1节-农夫过河问题

Note: 标注"//核心代码"的地方表示核心方法

运行此代码即能输出所有解决方案的文字描述

输入格式:

第一行两个整数 n，m，表示序列长度和询问个数（n <= 1e5，m <= 1e5）。

第二行 n 个整数，表示这个序列。

接下来 m 行，每行一个整数，表示询问其上下界。

序列索引范围 [1, ..., n]

输出格式

m 行，每行两个整数 a，b，表示每个询问的结果，即输出其上下界，表示区间 [a, b) 内有此数。

样例输入

10 5
1 2 2 2 4 5 5 7 9 10
2
7
5
4
8

样例输出

2 5
8 9
6 8
5 6
9 9


**************************************************************************/

#include <iostream>

const int maxn = 100500;

int a[maxn];

int getPos(int *a, int l, int r, int v);
int getUpperBound(int *a, int l, int r, int v);
int getLowerBound(int *a, int l, int r, int v);

int main()
{
    using namespace std;
    int n, m;
    cin >> n >> m;
    for(int i=1; i<=n; i++)
    {
        cin >> a[i];
    }
    for(int i=1; i<=m; i++)
    {
        int v;
        cin >> v;
        cout << getUpperBound(a, 1, n, v) << " " << getLowerBound(a, 1, n, v) << endl;
    }
    return 0;
}

int getPos(int *a, int l, int r, int v) //核心代码
{
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(a[mid] == v) 
            return mid;
        else if(a[mid] > v) 
            r = mid;
        else 
            l = mid + 1;
    }
    return l;
}
int getUpperBound(int *a, int l, int r, int v)  //核心代码
{
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(a[mid] >= v) 
            r = mid;
        else
            l = mid + 1;
    }
    return l;
}
int getLowerBound(int *a, int l, int r, int v)  //核心代码
{
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(a[mid] > v)
            r = mid;
        else l = mid + 1;
    }
    return l;
}