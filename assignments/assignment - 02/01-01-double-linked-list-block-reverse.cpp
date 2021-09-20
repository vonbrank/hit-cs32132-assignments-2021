#include <iostream>
#include <cstdio>
#include <ctime>

namespace vbk
{
    class Random
    {
    public:
        static int getNextInt()
        {
            static int seed = time(NULL);
            return seed = int(seed * 48271LL % 0x7fffffff);
        }
        static int getNextInt(int n)
        {
            return getNextInt() % (n + 1);
        }
        static int getNextInt(int a, int b)
        {
            return a + getNextInt() % (b - a + 1);
        }
    };

    void swapInt(int &a, int &b)
    {
        int c = a;
        a = b;
        b = c;
    }

    class LinkedList
    {
    private:
        class LinkedListNode
        {
        private:
            int value;
            LinkedListNode *next, *previous;
            friend class LinkedList;

        public:
            LinkedListNode(int value, LinkedListNode *next, LinkedListNode *previous)
            {
                this->value = value;
                this->next = next;
                this->previous = previous;
            }
        };
        LinkedListNode *_begin, *_end;
        int _length, _shit;

    public:
        class Iterator
        {
        private:
            LinkedListNode *iter;
            friend class LinkedList;

        public:
            Iterator()
            {
                iter = NULL;
            }

            int &operator*()
            {
                return iter->value;
            }
            Iterator operator++()
            {
                if (iter)
                    iter = iter->next;
                return *this;
            }
            bool operator!=(const Iterator &o) const
            {
                return this->iter != o.iter;
            }
        };
        LinkedList()
        {
            _begin = NULL;
            _end = NULL;
            _length = 0;
        }
        Iterator begin()
        {
            Iterator iter;
            iter.iter = _begin;
            return iter;
        }
        Iterator end()
        {
            Iterator iter;
            if (_end)
                iter.iter = _end->next;
            else
                iter.iter = NULL;
            return iter;
        }
        int &operator[](int pos)
        {
            if (_length == 0 || pos < 0 || pos >= _length)
                return _shit;
            LinkedListNode *now = _begin;
            for (int i = 0; i < pos; i++, now = now->next)
                ;
            return now->value;
        }
        void insert(int value)
        {
            _length++;
            if (_end == NULL)
            {
                _begin = new LinkedListNode(value, NULL, NULL);
                _end = _begin;
                return;
            }

            _end->next = new LinkedListNode(value, NULL, _end);
            _end = _end->next;
        }
        void erase()
        {
            if (_end == NULL)
                return;
            if (_length == 1)
            {
                delete _begin;
                _begin = _end = NULL;
                return;
            }
            LinkedListNode *previous = _end->previous;
            previous->next = NULL;
            delete _end;
            _end = previous;
            _length--;
        }
        void erase(int pos)
        {
            if (pos >= _length)
                return;

            LinkedListNode *now = _begin;
            for (int i = 0; i < pos; i++)
            {
                now = now->next;
            }
            LinkedListNode *previous = now->previous;
            LinkedListNode *next = now->next;

            if (previous)
                previous->next = next;
            if (next)
                next->previous = previous;

            if (pos == 0)
                _begin = next;
            if (pos == _length - 1)
                _end = previous;

            _length--;
        }
        void reverse(int a, int b)
        {
            if (a < 0 || b < 0 || a >= _length || b >= _length)
                return;
            LinkedListNode *now = _begin, *beginPoint, *endPoint;
            for (int i = 0; i < a; i++, now = now->next)
                ;
            beginPoint = now;

            now = _begin;
            for (int i = 0; i < b; i++, now = now->next)
                ;
            endPoint = now;

            while (!(beginPoint == endPoint || beginPoint->previous == endPoint))
            {
                swapInt(beginPoint->value, endPoint->value);
                beginPoint = beginPoint->next;
                endPoint = endPoint->previous;
            }
        }
        int length()
        {
            return _length;
        }
    };
}

int main()
{
    vbk::LinkedList linkedList;
    int n, k;
    printf("输入格式：\n");
    printf("一行两个整数 n, k ，分别表示链表的长度、题述中的 k 。\n");
    printf("（n个数将随机生成）\n");
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
    {
        linkedList.insert(vbk::Random::getNextInt(128));
    }
    for (vbk::LinkedList::Iterator it = linkedList.begin(); it != linkedList.end(); ++it)
    {
        printf("%d ", *it);
    }
    printf("\n");
    for (int i = 0; i < linkedList.length(); i += k)
    {
        linkedList.reverse(i, i + k - 1);
    }
    for (vbk::LinkedList::Iterator it = linkedList.begin(); it != linkedList.end(); ++it)
    {
        printf("%d ", *it);
    }
    printf("\n");
    return 0;
}