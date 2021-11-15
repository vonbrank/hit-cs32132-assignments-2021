//
// Created by VonBrank on 2021/11/6.
//

#include "Graph.h"
#include <stack>
#include <queue>
#include <algorithm>

void Graph::resetVis()
{
    for (int i = 0; i <= numOfNode; i++)
        vis[i] = false;
}

Graph::Graph(const Graph &g)
{
    numOfNode = numOfEdge = 0;
    head = nullptr;
    edges = nullptr;
}

Graph &Graph::operator=(const Graph &g)
{
    return *this;
}

Graph::Graph(int n, int m)
{
    numOfNode = n;
    numOfEdge = m;
    n += 10;
    m += 10;
    head = new int[n];
    edges = new Edge[m];
    nodeWeight = new int[n];
    vis = new bool[n];
    for (int i = 0; i < n; i++)
    {
        nodeWeight[i] = 0;
        head[i] = 0;
        edges[i] = {0, 0, 0};
    }

}

void Graph::addEdge(int u, int v, int w)
{
    static int cnt = 0;

    ++cnt;
    edges[cnt].to = v;
    edges[cnt].w = w;
    edges[cnt].next = head[u];
    head[u] = cnt;

}

void Graph::setNodeWeight(int u, int w)
{
    nodeWeight[u] = w;
}

int Graph::getNodeWeight(int u)
{
    return nodeWeight[u];
}

void Graph::getDFSRecursion(int u, std::vector<int> &ans)
{
    vis[u] = true;
    ans.push_back(u);
    for (int j = head[u]; j; j = edges[j].next)
    {
        int v = edges[j].to;
        int w = edges[j].w;
        if (!vis[v])
            getDFSRecursion(v, ans);
    }
}

std::pair<std::vector<int>, long long> Graph::getLongestPath()  //核心代码
{
    std::vector<int> inDegree(numOfNode + 10), outDegree(numOfNode + 10);
    std::vector<int> previous(numOfNode + 10), totalWeight(numOfNode + 10);
    for (int i = 0; i <= numOfNode; i++)
    {
        inDegree[i] = outDegree[i] = 0;
        previous[i] = i;
        totalWeight[i] = 0;
    }
    std::queue<int> q;
    for (int i = 1; i <= numOfNode; i++)
    {
        int u = i;
        for (int j = head[u]; j; j = edges[j].next)
        {
            int v = edges[j].to;
            outDegree[u]++;
            inDegree[v]++;
        }
    }
    for(int i=1; i<=numOfNode; i++)
    {
        if(inDegree[i] == 0)
        {
            q.push(i);
        }
    }
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int j=head[u]; j; j=edges[j].next)
        {
            int v = edges[j].to;
            int w = edges[j].w;
            inDegree[v]--;

            if(totalWeight[v] < totalWeight[u] + w)
            {
                totalWeight[v] = totalWeight[u] + w;
                previous[v] = u;
            }

            if(inDegree[v] == 0)
            {
                q.push(v);
            }
        }
    }
    int longestPathTarget = 0;
    for(int i=1; i<=numOfNode; i++)
    {
        if(totalWeight[longestPathTarget] < totalWeight[i])
        {
            longestPathTarget = i;
        }
    }
    std::vector<int> longestPath;
    for(int i=longestPathTarget; ; i=previous[i])
    {
        longestPath.push_back(i);
        if(i == previous[i]) break;
    }
    std::reverse(longestPath.begin(), longestPath.end());
    return std::pair<std::vector<int>, long long int>
            (longestPath, totalWeight[longestPathTarget] + nodeWeight[longestPathTarget]);
}
