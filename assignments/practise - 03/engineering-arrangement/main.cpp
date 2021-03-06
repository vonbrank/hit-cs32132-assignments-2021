/**************************************************************************

Author: 120L021403

Date: 2021-11-07

Description: HIT-数据结构与算法2021-实验三-工程安排

Note: 标注"//核心代码"的地方表示核心方法

运行此代码即能输出所有解决方案的文字描述


**************************************************************************/
#include <iostream>
#include "Graph.h"
#include <utility>
#include <vector>
int main()
{
    using namespace std;
    // std::cout << "Hello, World!" << std::endl;
    int n, m;
    cin >> n >> m;
    Graph graph(n, m);
    for(int i=1; i<=n; i++)
    {
        int weight;
        cin >> weight;
        graph.setNodeWeight(i, weight);
    }
    for(int i=1; i<=m; i++)
    {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v, graph.getNodeWeight(u));
    }
    pair<vector<int>, long long> ans = graph.getLongestPath();
    for(int i : ans.first)
    {
        cout << i << " ";
    }
    cout << endl;
    cout << ans.second << endl;
    return 0;
}
