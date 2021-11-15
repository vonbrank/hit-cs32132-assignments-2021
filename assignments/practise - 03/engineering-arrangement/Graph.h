//
// Created by VonBrank on 2021/11/6.
//

#ifndef GRAPH_TRAVERSAL_GRAPH_H
#define GRAPH_TRAVERSAL_GRAPH_H
#include <vector>
#include <utility>

class Graph
{
private:
    struct Edge
    {
        int to;
        long long w;
        int next;
    };
    struct DFSStack
    {
        bool endFlag;
        int currenStatus;
    };

    enum {maxNode = 100500, maxEdge = 100500};
    int numOfNode, numOfEdge;
    int *nodeWeight;
    int *head;
    bool *vis;
    Edge *edges;

    void resetVis();
    Graph(const Graph &g);
    Graph &operator=(const Graph &g);
    void getDFSRecursion(int u, std::vector<int> &ans);
public:
    explicit Graph(int n = maxNode, int m = maxEdge);
    void addEdge(int u, int v, int w = 1);
    void setNodeWeight(int u, int w);
    int getNodeWeight(int u);
    std::pair<std::vector<int>, long long>getLongestPath();

};


#endif //GRAPH_TRAVERSAL_GRAPH_H
