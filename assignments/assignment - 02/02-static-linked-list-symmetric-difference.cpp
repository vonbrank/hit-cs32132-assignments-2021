/**************************************************************************

Author: 120L021403

Date: 2021-09-19

Description: HIT-数据结构与算法2021-2.2节-求链表元素对称差

Note: 核心代码将标注为 "//核心代码"

样例：

输入：
20 20 50
47 24 20 41 34 44 7 7 30 26 25 8 28 35 28 1 15 25 6 37 
38 35 1 10 4 29 38 26 12 40 20 7 48 8 19 36 38 11 1 27 

输出：
A:
47 24 20 41 34 44 7 30 26 25 8 28 35 1 15 6 37 
B:
38 35 1 10 4 29 26 12 40 20 7 48 8 19 36 11 27
(A-B)∪(B-A):
47 24 41 34 44 30 25 28 15 6 37 38 10 4 29 12 40 48 19 36 11 27

**************************************************************************/

#include <iostream>
#include <cstdio>
#include <vector>

class StaticLinkedList
{
private:
    class StaticLinkedListNode //节点类定义
    {
    private:
        int data;
        int next;
        friend class StaticLinkedList;

    public:
        StaticLinkedListNode()
        {
            this->data = 0;
            this->next = 0;
        }
        StaticLinkedListNode(int data, int next)
        {
            this->data = data;
            this->next = next;
        }
    };
    int *heads;                  //链表头节点列表
    int sizeOfHeads;             //链表数量
    int capacityOfHeads;         //链表容量
    int spaceHead;               //节点池头节点
    int *lengthOfHeads;          //每个链表的长度
    StaticLinkedListNode *space; //节点池
    int sizeOfNodes;             //已存节点数量
    int capacityOfNodes;         //节点池容量

    void resizeHeads() //链表容量不足时自动扩容
    {
        if (sizeOfHeads == capacityOfHeads)
            capacityOfHeads *= 2;
        else if (sizeOfHeads <= capacityOfHeads / 4)
            capacityOfHeads /= 4;
        else
            return;

        int *cache = new int[capacityOfHeads];
        int *cacheLength = new int[capacityOfHeads];
        for (int i = 0; i < sizeOfHeads; i++)
        {
            cache[i] = heads[i];
            cacheLength[i] = lengthOfHeads[i];
        }
        delete[] heads;
        delete[] lengthOfHeads;
        heads = cache;
        lengthOfHeads = cacheLength;
    }
    int createNode(int data, int next) //从节点池中分配节点
    {
        if (sizeOfNodes == capacityOfNodes)
            return -1;
        int cache = spaceHead;
        spaceHead = space[spaceHead].next;
        space[cache].data = data;
        space[cache].next = next;
        sizeOfNodes++;
        return cache;
    }
    void deleteNode(int node) //回收节点
    {
        if (node == -1)
            return;
        space[node].next = spaceHead;
        spaceHead = node;
    }
    bool linkExist(int linkedList)
    {
        return !(linkedList >= sizeOfHeads || linkedList < 0);
    }

public:
    StaticLinkedList(int capacityOfNodes)
    {
        this->sizeOfHeads = 0;
        this->capacityOfHeads = 2;
        this->heads = new int[this->capacityOfHeads];
        this->lengthOfHeads = new int[this->capacityOfHeads];
        this->spaceHead = 0;
        this->sizeOfNodes = 0;
        this->capacityOfNodes = capacityOfNodes;
        this->space = new StaticLinkedListNode[this->capacityOfNodes];

        for (int i = 0; i < this->capacityOfNodes; i++)
        {
            if (i == this->capacityOfNodes - 1)
            {
                this->space[i].next = -1;
            }
            else
            {
                this->space[i].next = i + 1;
            }
        }
    }

    int createLinkedList() //创建链表
    {
        resizeHeads();
        heads[sizeOfHeads] = -1;
        lengthOfHeads[sizeOfHeads] = 0;
        return sizeOfHeads++;
    }

    void insert(int linkedList, int data) //插入节点
    {
        if (!linkExist(linkedList))
            return;
        if (find(linkedList, data) != -1)
            return;
        lengthOfHeads[linkedList]++;
        if (heads[linkedList] == -1)
        {
            int cache = createNode(data, -1);
            if (cache != -1)
                heads[linkedList] = cache;
            return;
        }
        int now = heads[linkedList];
        while (space[now].next != -1)
        {
            now = space[now].next;
        }
        int cache = createNode(data, -1);
        if (cache != -1)
            space[now].next = cache;
    }

    void eraseByValue(int linkedList, int data) //通过值来删除节点
    {
        if (!linkExist(linkedList))
            return;
        int previous = -1;
        int now = heads[linkedList];
        bool flag = false;
        while (now != -1)
        {
            if (space[now].data == data)
            {
                flag = true;
                break;
            }
            previous = now;
            now = space[now].next;
        }
        if (flag)
        {
            lengthOfHeads[linkedList]--;
            if (previous != -1)
                space[previous].next = space[now].next;
            else
                heads[linkedList] = space[now].next;
        }
        if (now != -1)
            deleteNode(now);
    }

    int length(int linkedList) //返回链表长度
    {
        if (!linkExist(linkedList))
            return 0;
        return lengthOfHeads[linkedList];
    }

    int find(int linkedList, int data)
    {
        if (!linkExist(linkedList))
            return -1;
        int pos = -1;
        int now = heads[linkedList];
        bool flag = false;
        while (now != -1)
        {
            pos++;
            if (space[now].data == data)
            {
                flag = true;
                break;
            }
            now = space[now].next;
        }
        if (!flag)
            pos = -1;
        return pos;
    }

    int get(int linkedList, int pos) //获取linkedList号链表的pos号元素
    {
        if (!linkExist(linkedList))
            return -1;
        int now = heads[linkedList];
        for (int i = 0; i < pos && now != -1; i++, now = space[now].next)
            ;
        if (now == -1)
            return 0;
        else
            return space[now].data;
    }

    int symmentryDifference(int linkedLisk1, int linkedList2) //核心代码
    {                                                         //求对称差
        int linkedList = createLinkedList();                  //创建临时链表
        for (int i = 0; i < length(linkedLisk1); i++)         //将A集合的数据拷贝至临时链表
        {
            insert(linkedList, get(linkedLisk1, i));
        }
        for (int i = 0; i < length(linkedList2); i++)
        {
            int x = get(linkedList2, i);
            if (find(linkedList, x) != -1) //遍历B集合，对于任一元素，若其在临时链表中存在，则删除之，否则添加之
            {
                eraseByValue(linkedList, x);
            }
            else
            {
                insert(linkedList, x);
            }
        }
        return linkedList; //返回临时链表作为结果
    }
};
int main()
{
    int n, m, maxn;
    scanf("%d %d %d", &n, &m, &maxn);
    StaticLinkedList sll((n + m + 10) * 2);
    int linkedList1 = sll.createLinkedList();
    int linkedList2 = sll.createLinkedList();
    int a = 1, b = 20, c = 15, d = 30;
    for (int i = 1; i <= n; i++)
    {
        int x;
        scanf("%d", &x);
        sll.insert(linkedList1, x);
    }
    for (int i = 1; i <= m; i++)
    {
        int x;
        scanf("%d", &x);
        sll.insert(linkedList2, x);
    }

    int linkedList = sll.symmentryDifference(linkedList1, linkedList2);

    printf("A:\n");
    for (int i = 0; i < sll.length(linkedList1); i++)
    {
        printf("%d ", sll.get(linkedList1, i));
    }
    printf("\n");

    printf("B:\n");
    for (int i = 0; i < sll.length(linkedList2); i++)
    {
        printf("%d ", sll.get(linkedList2, i));
    }
    printf("\n");

    printf("(A-B)∪(B-A):\n");
    for (int i = 0; i < sll.length(linkedList); i++)
    {
        printf("%d ", sll.get(linkedList, i));
    }
    return 0;
}
