/**************************************************************************

Author: 120L021403

Date: 2021-10-12

Description: HIT-数据结构与算法2021-3.2节-最近公共祖先

Note: 标注"//核心代码"的地方表示核心方法

输入格式：

第一行两个整数 n，m，表示二叉树的节点个数、询问次数。

接下来 n 行，每行两个整数 i，p_i，表示第 i 号节点的父节点编号为 p_i。

若 p_i = -1，则 i 是根节点。

最后 m 行，每行两个整数 x，y，表示查询编号为 x，y 节点的最近公共祖先（LCA）。

输出格式：

对于每个查询，输出其 LCA 的编号。

样例：

输入1：

10 5
1 -1
2 1
3 1
4 2
5 2
6 3
7 3
8 4
9 4
10 5
4 3
8 10
3 6
9 9
10 7

输出1：

1
2
3
9
1


**************************************************************************/

#include <iostream>
#include <vector>
using namespace std;

class BinaryTree
{
protected:
    class BinaryTreeNode
    {
    private:
        int data;
        int fa, lchild, rchild;
        friend class BinaryTree;
        friend class BinaryTreeLCA;

    public:
        BinaryTreeNode()
            : data(0), lchild(0), rchild(0) {}
        BinaryTreeNode(int data)
            : data(data), lchild(0), rchild(0) {}
    };
    int root;
    int _size;
    BinaryTreeNode *nodes;

public:
    BinaryTree()
        : root(-1), _size(0), nodes(nullptr) {}
    BinaryTree(const vector<pair<int, int>> &edges, int size)
    {
        _size = size;
        nodes = new BinaryTreeNode[_size + 10];
        for (int i = 1; i <= _size; i++)
            nodes[i].data = i;
        for (int i = 0; i < edges.size(); i++)
        {
            int u = edges[i].first;
            int v = edges[i].second;
            if (v == -1)
            {
                root = u;
            }
            else
            {
                nodes[u].fa = v;
                if (nodes[v].lchild)
                    nodes[v].rchild = u;
                else
                    nodes[v].lchild = u;
            }
        }
    }
    ~BinaryTree()
    {
        delete[] nodes;
    }
};

class BinaryTreeLCA : public BinaryTree
{
private:
    int *nodeTop;
    int *nodeSize;
    int *nodeSon;
    int *nodeDepth;

    void getSize(int u)
    {
        nodeDepth[u] = nodeDepth[nodes[u].fa] + 1;
        nodeSize[u] = 1;
        if (nodes[u].lchild)
        {
            getSize(nodes[u].lchild);
            nodeSize[u] += nodeSize[nodes[u].lchild];
        }

        if (nodes[u].rchild)
        {
            getSize(nodes[u].rchild);
            nodeSize[u] += nodeSize[nodes[u].rchild];
        }
        nodeSon[u] = nodeSize[nodes[u].lchild] > nodeSize[nodes[u].rchild]
                         ? nodes[u].lchild
                         : nodes[u].rchild;
    }
    void getTop(int u)
    {
        if (!u)
            return;
        if (nodeSon[nodes[u].fa] == u)
            nodeTop[u] = nodeTop[nodes[u].fa];
        else
            nodeTop[u] = u;
        getTop(nodeSon[u]);
        if (nodeSon[u] == nodes[u].lchild)
            getTop(nodes[u].rchild);
        else
            getTop(nodes[u].lchild);
    }

public:
    BinaryTreeLCA(const vector<pair<int, int>> &edges, int size) : BinaryTree(edges, size)
    {
        nodeTop = new int[_size + 10];
        nodeSize = new int[_size + 10];
        nodeSon = new int[_size + 10];
        nodeDepth = new int[_size + 10];
        getSize(root);
        getTop(root);
    }
    int getLCA(int x, int y) //核心代码
    {
        if (!(x >= 1 && x <= _size && y >= 1 && y <= _size))
            return 0;
        while (nodeTop[x] != nodeTop[y])
        {
            if (nodeDepth[nodeTop[x]] < nodeDepth[nodeTop[y]])
                swap(x, y);
            x = nodes[nodeTop[x]].fa;
        }
        return nodeDepth[x] > nodeDepth[y] ? y : x;
    }
    void debug()
    {
        cout << "debug: " << endl;
        for (int i = 1; i <= _size; i++)
        {
            cout << nodeSize[i] << " ";
        }
        cout << endl;
        for (int i = 1; i <= _size; i++)
        {
            cout << nodeSon[i] << " ";
        }
        cout << endl;
        for (int i = 1; i <= _size; i++)
        {
            cout << nodeTop[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges;
    for (int i = 1; i <= n; i++)
    {
        int u, v;
        cin >> u >> v;
        edges.push_back(pair<int, int>(u, v));
    }
    BinaryTreeLCA binaryTreeLCA(edges, n);
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        cin >> x >> y;
        cout << binaryTreeLCA.getLCA(x, y) << endl;
    }
    // binaryTreeLCA.debug();
    return 0;
}