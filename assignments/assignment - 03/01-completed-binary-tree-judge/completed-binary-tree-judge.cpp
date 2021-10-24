/**************************************************************************

Author: 120L021403

Date: 2021-10-12

Description: HIT-数据结构与算法2021-3.1节-完全二叉树的判定

Note: 标注"//核心代码"的地方表示核心方法

输入格式：

第一行一个整数 n，表示二叉树的节点个数。

接下来 n 行，每行两个整数 i，p_i，表示第 i 号节点的父节点编号为 p_i。

若 p_i = -1，则 i 是根节点。

输入保证是一棵二叉树。

输出格式：

如果是完全二叉树，则输出YES，否则输出NO。

样例：

输入1：

10
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

输出1：

YES


输入2：

10
1 -1
2 1
3 1
4 2
5 2
6 3
7 5
8 4
9 4
10 5

输出2：

NO


**************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;
class BinaryTree
{
private:
    class BinaryTreeNode
    {
    private:
        int data;
        int lchild, rchild;
        friend class BinaryTree;

    public:
        BinaryTreeNode()
            : data(0), lchild(0), rchild(0) {}
        BinaryTreeNode(int data)
            : data(data), lchild(0), rchild(0) {}
    };
    int root;
    int _size;
    BinaryTreeNode *nodes;
    bool _isCompleted;
    bool completionJudger() //核心代码
    {
        queue<int> q;
        q.push(root);
        int count = 0;
        bool nullPointerExists = false;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            if (u)
            {
                count++;
                if (nullPointerExists)
                    return false;
                q.push(nodes[u].lchild);
                q.push(nodes[u].rchild);
            }
            else
            {
                nullPointerExists = true;
                if (count == _size)
                    return true;
            }
        }
        return false;
    }

public:
    BinaryTree()
        : root(-1), _size(0), nodes(nullptr), _isCompleted(false) {}
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
                if (nodes[v].lchild)
                    nodes[v].rchild = u;
                else
                    nodes[v].lchild = u;
            }
        }
        _isCompleted = completionJudger();
    }
    ~BinaryTree()
    {
        delete[] nodes;
    }
    bool isCompleted() const
    {
        return _isCompleted;
    }
};

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> edges;
    for (int i = 1; i <= n; i++)
    {
        int u, v;
        cin >> u >> v;
        edges.push_back(pair<int, int>(u, v));
    }
    BinaryTree binaryTree(edges, n);
    cout << (binaryTree.isCompleted() ? "YES" : "NO") << endl;
    return 0;
}