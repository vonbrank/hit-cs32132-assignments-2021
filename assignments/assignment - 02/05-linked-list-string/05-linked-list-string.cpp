/**************************************************************************

Author: 120L021403

Date: 2021-09-29

Description: HIT-数据结构与算法2021-2.5节-链表实现字符串的查找、切片

Note: 标注"//核心代码的地方表示核心方法"

输入格式：

第一行一个字符串s，表示要操作的字符串

第二行一个整数，表示操作个数

接下来 n 行，每行有以下操作的一种：

1 t  如果 t 是 s 的子串，则输出开始位置在 s 中的索引，从0开始算；否则输出-1

2 a b  输出 s 中处于 [a, b] 区间的子串，越界部分不输出

输出格式：

n 行，对于每种操作，输出其结果

样例：

输入：

YmBYpuUnvhaNrNluLeJzqxvwHrQJyBliGPSCCUTcFqSXlmdBAN
26
2 3 31
1 iGPSCCU
2 3 4
2 29 45
1 vhaNrNluLeJzqxvwHrQJyBliGPSCCUTcFqSXlmdBAN
1 liGPSCCUTcFqSXlm
1 qSXlmdB
2 5 44
1 GPSCC
1 nvhaNrNluLeJzqxvwHrQJyBliGPSCCUTcFqSXlmdBANabc
1 uUnvhaNrNluLeJzqxvwHrQJyBliGP
2 2 8
1 BYpuUnvhaNrNluLeJzqxvwHrQJyBliGPSC
1 haNrNluLeJzqxv
1 TcFqSXlm
1 vhaNrNluLeJzqx
2 31 32
2 20 23
2 45 47
1 rQJyBliGPS
2 12 46
1 liGPSCCUTcFq
1 UnvhaNrNluLe
2 34 34
2 37 49
1 abcPSCCUTcFqSXl


输出：

YpuUnvhaNrNluLeJzqxvwHrQJyBli
31
Yp
BliGPSCCUTcFqSXlm
8
30
41
uUnvhaNrNluLeJzqxvwHrQJyBliGPSCCUTcFqSXl
32
-1
5
BYpuUnv
2
9
38
8
iG
qxvw
mdB
25
rNluLeJzqxvwHrQJyBliGPSCCUTcFqSXlmd
30
6
S
UTcFqSXlmdBAN
-1


**************************************************************************/

#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <cstring>

class LinkedListString
{
private:
    class Node //节点类
    {
    private:
        char _data;
        Node *_next;

    public:
        Node(char _data, Node *_next)
        {
            this->_data = _data;
            this->_next = _next;
        }
        char &data()
        {
            return _data;
        }
        Node *&next()
        {
            return _next;
        }
    };

    Node *head;
    int _length;

public:
    LinkedListString()
    {
        head = NULL;
        _length = 0;
    }
    LinkedListString(const char *s) //初始化链表
    {
        head = NULL;
        _length = 0;
        int len = strlen(s);
        for (int i = 0; i < len; i++)
        {
            this->push(s[i]);
        }
    }
    void push(char _data) //从末尾插入字符
    {
        if (_data == ' ' || _data == '\n' || _data == '\r' || _data == '\t')
            return;
        _length++;
        if (!head)
        {
            head = new Node(_data, NULL);

            return;
        }
        Node *now = head;
        while (now->next())
        {
            now = now->next();
        }
        now->next() = new Node(_data, NULL);
    }
    void pop() //删除末尾元素
    {
        if (!head)
        {
            return;
        }
        Node *pre = NULL;
        Node *now = head;
        while (now->next())
        {
            pre = now;
            now = now->next();
        }
        if (pre)
            pre->next() = NULL;
        delete now;
        _length--;
    }
    char &get(int _index) //取得位置为 i 的元素值，越界访问将报异常
    {
        if (_index >= _length || _index < 0)
        {
            throw std::out_of_range("Linked List Index Out Of Bounds Exception.");
        }
        Node *now = head;
        for (int i = 0; i < _index; i++, now = now->next())
            ;
        return now->data();
    }
    int length() //获取字符串长度
    {
        return _length;
    }
    //核心代码
    int index(const LinkedListString &s) //若s为对象本身的子串，则返回其在对象本身的索引，否则返回-1
    {
        if (!this->head || !s.head)
            return -1;
        int cnt = 0;
        for (Node *i = this->head; i; i = i->next(), cnt++)
        {
            bool flag = true;
            Node *j, *k;
            for (j = i, k = s.head; j && k; j = j->next(), k = k->next())
            {
                // printf("%c %c\n", j->data(), k->data());
                if (j->data() != k->data())
                {
                    flag = false;
                    break;
                }
            }
            if (flag && !k)
                return cnt;
        }
        return -1;
    }
    //核心代码
    LinkedListString subString(int m, int n) //返回对象在区间[m, n]内的子串
    {
        LinkedListString res;
        Node *now = this->head;
        if (!now)
            return res;
        for (int i = 0; i < _length; i++, now = now->next())
        {
            if (i >= m && i <= n)
            {
                res.push(now->data());
            }
        }
        return res;
    }
};

int main()
{
    // freopen("output.txt", "w", stdout);
    printf("输入输出格式在文件上方注释有详细说明，请保证数据合法\n");
    printf("推荐使用data-generator.cpp生成数据，其将自动输出至input.txt\n");
    LinkedListString s;
    char c;
    while ((c = getchar()) != '\n')
    {
        s.push(c);
    }
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            char c;
            LinkedListString cache;
            while ((c = getchar()) != '\n')
            {
                cache.push(c);
            }
            printf("%d\n", s.index(cache));
        }
        else if (op == 2)
        {
            int a, b;
            scanf("%d %d", &a, &b);
            LinkedListString cache = s.subString(a, b);
            for (int j = 0; j < cache.length(); j++)
            {
                printf("%c", cache.get(j));
            }
            printf("\n");
        }
    }
    return 0;
}