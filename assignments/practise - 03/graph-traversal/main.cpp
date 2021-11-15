/**************************************************************************

Author: 120L021403

Date: 2021-11-07

Description: HIT-数据结构与算法2021-实验三-图的遍历

Note: 标注"//核心代码"的地方表示核心方法

运行此代码即能输出所有解决方案的文字描述

**************************************************************************/

#include <iostream>
#include <vector>
#include "Graph.h"

int main()
{
    using namespace std;
//    std::cout << "Hello, World!" << std::endl;
    int n, m, s;
    cin >> n >> m >> s;
    Graph graph(n, m);
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    vector<int> v = graph.getDFSNonRecursion(s);
    for (int i : v)
    {
        cout << i << " ";
    }
    cout << endl;

    v = graph.getDFSRecursion(s);
    for (int i : v)
    {
        cout << i << " ";
    }
    cout << endl;

    v = graph.getBFS(s);
    for (int i : v)
    {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
