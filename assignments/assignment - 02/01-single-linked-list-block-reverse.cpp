/**************************************************************************

Author: 120L021403

Date: 2021-09-16

Description: HIT-数据结构与算法2021-2.1节-链表块转置

**************************************************************************/
#include <iostream>
#include <cstdio>
#include <ctime>

int shitInt; //针对链表非法访问，返回一个随机变量的引用

class Random //随机数生成器
{
public:
    static int getNextInt() //随机生成一个int
    {
        static int seed = time(NULL);
        return seed = int(seed * 48271LL % 0x7fffffff);
    }
    static int getNextInt(int n) //生成[0, n]范围内的int
    {
        return getNextInt() % (n + 1);
    }
    static int getNextInt(int a, int b) //生成[a, b]内的int
    {
        return a + getNextInt() % (b - a + 1);
    }
};

void swapInt(int &a, int &b) //交换变量的值
{
    int c = a;
    a = b;
    b = c;
}

class SingleLinkedList //单向链表类
{
private:
    class SingleLinkedListNode //链表节点类
    {
    private:
        int _data;
        SingleLinkedListNode *_next;
        friend class SingleLinkedList;

    public:
        SingleLinkedListNode(int _data, SingleLinkedListNode *_next) //初始化节点
        {
            this->_data = _data;
            this->_next = _next;
        }
    };

    SingleLinkedListNode *_head; //链表头
    int _length;                 //链表长度

public:
    class Iterator //定义链表迭代器，实现自定义链表遍历方式
    {
    private:
        SingleLinkedListNode *_it;

    public:
        Iterator()
        {
            _it = NULL;
        }
        Iterator(SingleLinkedListNode *it)
        {
            this->_it = it;
        }
        int &operator*() //*it表示取得it这个指针在链表中指向的值
        {
            if (_it)
                return _it->_data;
            else
                return shitInt;
        }
        Iterator operator++() //重载++运算符
        {
            if (_it)
                _it = _it->_next;
            return *this;
        }
        bool isNULL() //判断迭代器是否为空
        {
            return _it == NULL;
        }
    };

    SingleLinkedList()
    {
        _head = NULL;
        _length = 0;
    }
    void insert(int _data) //在链表末插入值为data的节点
    {
        _length++;
        if (_head == NULL)
        {
            _head = new SingleLinkedListNode(_data, NULL);
            return;
        }
        SingleLinkedListNode *now = _head;
        while (now->_next) //插入链表末尾，时间复杂度O(n)
        {
            now = now->_next;
        }
        now->_next = new SingleLinkedListNode(_data, NULL);
    }
    void insert(int pos, int data) //在pos位置插入值为data的节点
    {
        _length++;
        if (pos <= 0)
        {
            SingleLinkedListNode *tmp = new SingleLinkedListNode(data, _head);
            _head = tmp;
            return;
        }
        else if (pos >= _length)
        {
            erase(data);
            return;
        }
        SingleLinkedListNode *previous = NULL;
        SingleLinkedListNode *now = _head;
        for (int i = 0; i < pos - 1; i++, now = now->_next) //获取位置为pos的节点，将新节点插到其之前
            ;
        previous = now;
        now = now->_next;
        previous->_next = new SingleLinkedListNode(data, now);
    }
    void erase() //删除链表末节点
    {
        if (_head == NULL)
            return;
        SingleLinkedListNode *previous = NULL;
        SingleLinkedListNode *now = _head;
        while (now->_next)
        {
            previous = now;
            now = now->_next;
        }
        if (previous)
            previous->_next = NULL;
        delete now;
        _length--;
    }
    void erase(int pos) //删除位置为pos的节点
    {
        if (pos < 0 || pos >= _length)
            return;

        SingleLinkedListNode *previous = NULL;
        SingleLinkedListNode *now = _head;

        for (int i = 0; i < pos; i++, previous = now, now = now->_next)
            ;
        if (previous)
            previous->_next = now->_next;
        else
            _head = now->_next;
        delete now;
        _length--;
    }
    int &operator[](int pos) //重载[]运算符，实现用linkedList[i]访问链表第i个元素值
    {
        if (_length == 0 || pos < 0 || pos >= _length)
            return shitInt;
        SingleLinkedListNode *now = _head;
        for (int i = 0; i < pos; i++, now = now->_next)
            ;
        return now->_data;
    }
    void reverse(int a, int b) //逆置链表区间[a, b]内的节点
    {
        if (a < 0 || b >= _length || b < 0 || b >= _length || a > b)
            return;
        SingleLinkedListNode *previous = _head;
        SingleLinkedListNode *last;
        SingleLinkedListNode *now = _head;
        SingleLinkedListNode *next = _head;
        //获取翻转区间的前驱与后继
        for (int i = 0; i < a - 1; i++, previous = previous->_next)
            ;
        if (a == 0)
            previous = NULL;
        for (int i = 0; i < b + 1; i++, next = next->_next)
            ;
        if (previous)
            now = previous->_next;
        last = now;
        now = now->_next;
        last->_next = next; //翻转区间的头节点的next指向翻转区间的后继
        while (now != next) //遍历翻转区间，使每个节点的next指针指向其前驱
        {
            SingleLinkedListNode *tmp = now->_next;
            now->_next = last;
            last = now;
            now = tmp;
        }
        if (previous) //翻转区间的前驱的next指向翻转区间的尾节点
            previous->_next = last;
        else
            _head = last;
    }
    int length() //返沪链表的长度
    {
        return _length;
    }
    Iterator begin() //返回链表头节点迭代器
    {
        Iterator it(_head);
        return it;
    }
};

int main()
{
    int n, k;
    SingleLinkedList singleLinkedList;

    printf("输入格式：\n");
    printf("一行两个整数 n, k ，分别表示链表的长度、题述中的 k 。\n");
    printf("（n个数将随机生成）\n");
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; i++)
    {
        singleLinkedList.insert(Random::getNextInt(100));
    }

    for (int i = 0; i < singleLinkedList.length(); i++)
    {
        printf("%d ", singleLinkedList[i]); //正序遍历输出链表，用下标访问
    }
    printf("\n");
    for (int i = 0; i < n; i += k)
    {
        singleLinkedList.reverse(i, i + k - 1); //翻转区间
    }

    for (SingleLinkedList::Iterator it = singleLinkedList.begin(); !it.isNULL(); ++it)
    {
        printf("%d ", *it); //使用客制化迭代器遍历翻转后的链表
    }
    printf("\n");
    return 0;
}