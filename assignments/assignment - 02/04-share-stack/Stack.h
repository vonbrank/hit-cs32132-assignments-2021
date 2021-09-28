#ifndef STACK_H
#define STACK_H

#include "Vector.h"

template <class T>
class StaticStack
{
private:
    class StaticStackNode
    {
    private:
        T _data;
        int _next;

    public:
        StaticStackNode();
        T &data();
        int &next();
    };
    Vector<int> _top;                //栈顶
    Vector<int> _size;               //每个栈的大小
    int _spaceHead;                  //节点池头节点
    int _spaceSize;                  //节点池大小
    int _capacity;                   //静态栈总容量
    StaticStackNode *_data;          //节点池
    int newNode(T _data, int _next); //新建节点，并返回其位置
    void deleteNode(int pos);        //删除位置为pos的节点

public:
    StaticStack();                 //初始化静态栈
    StaticStack(int _capacity);    //初始化容量为_capacity的静态栈
    ~StaticStack();                //析构函数
    int createStack();             //创建栈，并返回其编号
    T top(int index);              //返回栈顶值
    void push(int index, T value); //向编号为head的栈顶压入value
    void pop(int index);           //弹出head栈顶的元素
    bool empty(int index);         //栈判空
    int numberOfStack();           //返回栈的数量
    // void debug();
};

template <class T>
StaticStack<T>::StaticStackNode::StaticStackNode()
{
    _next = -1;
}

template <class T>
T &StaticStack<T>::StaticStackNode::data()
{
    return this->_data;
}

template <class T>
int &StaticStack<T>::StaticStackNode::next()
{
    return this->_next;
}

template <class T>
StaticStack<T>::StaticStack()
{
    StaticStack(1);
}

template <class T>
StaticStack<T>::StaticStack(int _capacity)
{
    this->_capacity = _capacity;
    _spaceHead = 0;
    _spaceSize = _capacity;
    _data = new StaticStackNode[_capacity];
    for (int i = 0; i < _capacity; i++)
    {
        _data[i].next() = i + 1;
    }
    _data[_capacity - 1].next() = -1;
}

template <class T>
StaticStack<T>::~StaticStack()
{
    delete[] _data;
}

template <class T>
int StaticStack<T>::createStack()
{
    _top.pushBack(-1);
    _size.pushBack(0);
    return _top.size() - 1;
}

template <class T>
T StaticStack<T>::top(int head)
{
    if (empty(head))
        return 0;
    return _data[_top[head]].data();
}

template <class T>
void StaticStack<T>::push(int head, T value)
{
    int cache = newNode(value, _top[head]);
    _top[head] = cache;
    _size[head]++;
}

template <class T>
void StaticStack<T>::pop(int head)
{
    if (empty(head))
        return;
    int cache = _top[head];
    _top[head] = _data[cache].next();
    deleteNode(cache);
    _size[head]--;
}

template <class T>
int StaticStack<T>::newNode(T _data, int _next)
{
    int cache = _spaceHead;
    _spaceHead = this->_data[cache].next();
    _spaceSize--;
    this->_data[cache].data() = _data;
    this->_data[cache].next() = _next;
    return cache;
}

template <class T>
void StaticStack<T>::deleteNode(int pos)
{
    int cache = pos;
    _data[cache].next() = _spaceHead;
    _spaceHead = cache;
    _spaceSize++;
}

template <class T>
bool StaticStack<T>::empty(int index)
{
    return _size[index] == 0;
}

template <class T>
int StaticStack<T>::numberOfStack()
{
    return _top.size();
}

// template <class T>
// void StaticStack<T>::debug()
// {
//     int cnt = 0;
//     for (int i = _spaceHead; i != -1; i = _data[i].next())
//     {
//         printf("%d ", i);
//         cnt++;
//     }
//     printf("\n%d", cnt);
// }
#endif