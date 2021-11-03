#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class BinaryTree
{
private:
    class BinaryTreeNode
    {
    private:
        int data;
        BinaryTreeNode *lchild, *rchild;
        friend class BinaryTree;

    public:
        BinaryTreeNode(int data, BinaryTreeNode *lchild, BinaryTreeNode *rchild);
    };
    class GetOrderStackNode
    {
    private:
        friend class BinaryTree;
        int status; //当前需进行的操作：0: 处理根节点，1: 需递归左子树，2: 需递归右子树，3: 退栈。
        BinaryTreeNode *rt;
        vector<int> &currentOrder;

    public:
        GetOrderStackNode(BinaryTreeNode *rt, vector<int> &currentOrder);
        GetOrderStackNode(BinaryTreeNode *rt, vector<int> &currentOrder, int status);
    };
    int size;
    vector<int> preorder, midorder, postorder;
    BinaryTreeNode *root;
    BinaryTreeNode *build(vector<int> &preorder, vector<int> &midorder);
    void getPostorder(BinaryTreeNode *rt, vector<int> &currentPostorder);

public:
    BinaryTree(vector<int> &preorder, vector<int> &midorder);
    const vector<int> &getPostorder();
    const vector<int> &getPreorderNonRecursion();
    const vector<int> &getMidorderNonRecursion();
    const vector<int> &getPostorderNonRecursion();
};

int main()
{
    int n;
    cin >> n;
    vector<int> preorder, midorder, postorder;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        preorder.push_back(x);
    }
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        midorder.push_back(x);
    }
    BinaryTree binaryTree(preorder, midorder);

    preorder = binaryTree.getPreorderNonRecursion();
    for (int i = 0; i < preorder.size(); i++)
    {
        cout << preorder[i] << " ";
    }
    cout << endl;

    midorder = binaryTree.getMidorderNonRecursion();
    for (int i = 0; i < midorder.size(); i++)
    {
        cout << midorder[i] << " ";
    }
    cout << endl;

    postorder = binaryTree.getPostorderNonRecursion();
    for (int i = 0; i < postorder.size(); i++)
    {
        cout << postorder[i] << " ";
    }
    cout << endl;
    return 0;
}

BinaryTree::BinaryTreeNode::BinaryTreeNode(int data, BinaryTreeNode *lchild, BinaryTreeNode *rchild)
{
    this->data = data;
    this->lchild = lchild;
    this->rchild = rchild;
}

BinaryTree::BinaryTree(vector<int> &preorder, vector<int> &midorder)
{
    if (preorder.size() != midorder.size())
        return;
    root = build(preorder, midorder);
    getPostorder(root, postorder);
}

BinaryTree::BinaryTreeNode *BinaryTree::build(vector<int> &preorder, vector<int> &midorder)
{
    if (preorder.size() == midorder.size() && preorder.size() == 0)
        return nullptr;
    if (preorder.size() == midorder.size() && preorder.size() == 1)
        return new BinaryTreeNode(preorder[0], nullptr, nullptr);
    bool flagLeftChild = true;
    vector<int> leftChildPreorder;
    vector<int> leftChildMidorder;
    vector<int> rightChildPreorder;
    vector<int> rightChildMidorder;
    for (int i = 0; i < midorder.size(); i++)
    {
        if (midorder[i] == preorder[0])
        {
            flagLeftChild = false;
            continue;
        }
        if (flagLeftChild)
        {
            leftChildPreorder.push_back(preorder[i + 1]);
            leftChildMidorder.push_back(midorder[i]);
        }
        else
        {
            rightChildPreorder.push_back(preorder[i]);
            rightChildMidorder.push_back(midorder[i]);
        }
        // cout << midorder[i] << " ";
    }
    // cout << endl;
    BinaryTreeNode *nowRoot =
        new BinaryTreeNode(preorder[0],
                           build(leftChildPreorder, leftChildMidorder),
                           build(rightChildPreorder, rightChildMidorder));
    return nowRoot;
}

void BinaryTree::getPostorder(BinaryTreeNode *rt, vector<int> &currentPostorder)
{
    if (rt == nullptr)
        return;
    getPostorder(rt->lchild, currentPostorder);
    getPostorder(rt->rchild, currentPostorder);
    currentPostorder.push_back(rt->data);
}

const vector<int> &BinaryTree::getPostorder()
{
    return postorder;
}

BinaryTree::GetOrderStackNode::GetOrderStackNode(BinaryTreeNode *rt, vector<int> &currentOrder)
    : rt(rt), currentOrder(currentOrder) {}

BinaryTree::GetOrderStackNode::GetOrderStackNode(BinaryTreeNode *rt, vector<int> &currentOrder, int status)
    : rt(rt), currentOrder(currentOrder), status(status) {}

const vector<int> &BinaryTree::getPreorderNonRecursion()
{
    stack<GetOrderStackNode> stk;
    preorder.clear();
    stk.push(GetOrderStackNode(root, preorder, 0));
    while (!stk.empty())
    {
        if (stk.top().status == 0)
        {
            stk.top().status = 1;
            preorder.push_back(stk.top().rt->data);
        }
        else if (stk.top().status == 1)
        {
            stk.top().status = 2;
            if (stk.top().rt->lchild)
                stk.push(GetOrderStackNode(stk.top().rt->lchild, preorder, 0));
        }
        else if (stk.top().status == 2)
        {
            stk.top().status = 3;
            if (stk.top().rt->rchild)
                stk.push(GetOrderStackNode(stk.top().rt->rchild, preorder, 0));
        }
        else
            stk.pop();
    }
    return preorder;
}
const vector<int> &BinaryTree::getMidorderNonRecursion()
{
    stack<GetOrderStackNode> stk;
    midorder.clear();
    stk.push(GetOrderStackNode(root, midorder, 1));
    while (!stk.empty())
    {
        if (stk.top().status == 0)
        {
            stk.top().status = 2;
            midorder.push_back(stk.top().rt->data);
        }
        else if (stk.top().status == 1)
        {
            stk.top().status = 0;
            if (stk.top().rt->lchild)
                stk.push(GetOrderStackNode(stk.top().rt->lchild, midorder, 1));
        }
        else if (stk.top().status == 2)
        {
            stk.top().status = 3;
            if (stk.top().rt->rchild)
                stk.push(GetOrderStackNode(stk.top().rt->rchild, midorder, 1));
        }
        else
            stk.pop();
    }
    return midorder;
}
const vector<int> &BinaryTree::getPostorderNonRecursion()
{
    stack<GetOrderStackNode> stk;
    postorder.clear();
    stk.push(GetOrderStackNode(root, postorder, 1));
    while (!stk.empty())
    {
        if (stk.top().status == 0)
        {
            stk.top().status = 3;
            postorder.push_back(stk.top().rt->data);
        }
        else if (stk.top().status == 1)
        {
            stk.top().status = 2;
            if (stk.top().rt->lchild)
                stk.push(GetOrderStackNode(stk.top().rt->lchild, postorder, 1));
        }
        else if (stk.top().status == 2)
        {
            stk.top().status = 0;
            if (stk.top().rt->rchild)
                stk.push(GetOrderStackNode(stk.top().rt->rchild, postorder, 1));
        }
        else
            stk.pop();
    }
    return postorder;
}

/*
11
1 2 3 4 5 6 7 8 9 10 11
3 2 5 4 6 1 8 7 10 9 11
*/