//
// Created by VonBrank on 2021/11/6.
//

#include "Graph.h"
#include <stack>
#include <queue>

void Graph::resetVis()
{
    for(int i=0; i<=numOfNode; i++)
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
    for(int i=0; i<n; i++)
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
    for(int j=head[u]; j; j=edges[j].next)
    {
        int v = edges[j].to;
        int w = edges[j].w;
        if(!vis[v])
            getDFSRecursion(v, ans);
    }
}

std::vector<int> Graph::getDFSRecursion(int s)
{
    for(int i=1; i<=numOfNode; i++)
        vis[i] = false;
    std::vector<int> ans;
    getDFSRecursion(s, ans);
    return ans;
}

std::vector<int> Graph::getDFSNonRecursion(int s)//核心代码
{
    using namespace std;
    for(int i=1; i<=numOfNode; i++)
        vis[i] = false;
    vector<int> ans;
    stack<DFSStack> stk;
    stk.push(DFSStack{false, head[s]});
    vis[s] = true;
    ans.push_back(s);
    while(!stk.empty())
    {
        DFSStack &now = stk.top();
        if(now.endFlag)
            stk.pop();
        else
        {
            int v = edges[now.currenStatus].to;
            int w = edges[now.currenStatus].w;
            if(!vis[v])
            {
                vis[v] = true;
                stk.push(DFSStack{false, head[v]});
                ans.push_back(v);
            }
            if(edges[now.currenStatus].next)
            {
                now.currenStatus = edges[now.currenStatus].next;
            }
            else
            {
                now.endFlag = true;
            }
        }
    }
    return ans;
}

std::vector<int> Graph::getBFS(int s)
{
    using namespace std;
    resetVis();
    vector<int> ans;
    queue<int> q;
    q.push(s);
    vis[s] = true;
    while (!q.empty())
    {
        int u = q.front();

        q.pop();
        ans.push_back(u);
        for(int j=head[u]; j; j=edges[j].next)
        {
            int v = edges[j].to;
            if(!vis[v])
            {
                q.push(v);
                vis[v] = true;
            }

        }
    }
    return ans;
}
