/**************************************************************************

Author: 120L021403

Date: 2021-09-20

Description: HIT-数据结构与算法2021-2.3节-链表大作业

Note: 
- 由于不允许使用STL，我将部分需要的STL库手动实现。
- 链表核心部分将以注释 “//核心代码标注” 

--------------------------------------------------------------------------

样例：

输入：


输出：


**************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>

class Type
{
public:
    static bool isAlpha(char c);
    static bool isDigit(char c);
    static bool charCompare(char a, char b);
    static char toLower(char c);
    static char toUpper(char c);
};

bool Type::isAlpha(char c)
{
    bool res = false;
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        res = true;
    return res;
}

bool Type::isDigit(char c)
{
    bool res = false;
    if (c >= '0' && c <= '9')
        res = true;
    return res;
}

bool Type::charCompare(char a, char b)
{
    if (!((isAlpha(a) || isDigit(b)) && (isAlpha(b) || isDigit(b))))
        return a < b;
    if (isAlpha(a) && isAlpha(b))
    {
        if (toLower(a) == toLower(b))
            return a < b;
        else
            return toLower(a) < toLower(b);
    }
    else if (isDigit(a) && isDigit(b))
    {
        return a < b;
    }
    else if (isDigit(a) && isAlpha(b))
    {
        return true;
    }
    else if (isAlpha(a) && isDigit(b))
    {
        return false;
    }
    return false;
}

char Type::toLower(char c)
{
    if (!isAlpha(c))
        return c;
    if (c >= 'A' && c <= 'Z')
        c = c - 'A' + 'a';
    return c;
}

char Type::toUpper(char c)
{
    if (!isAlpha(c))
        return c;
    if (c >= 'a' && c <= 'z')
        c = c - 'a' + 'A';
    return c;
}

class String
{
private:
    int _size;
    char *_data;

public:
    String();
    String(const char *s);
    String operator=(const char *s);
    bool operator==(const String &s) const;
    bool operator!=(const String &s) const;
    bool operator<(const char *s) const;
    bool operator<(const String &s) const;
    char &operator[](int i);
    char *data() const;
    int size();
};

String::String()
{
    _size = 0;
    _data = new char[1];
    _data[0] = '\0';
}

String::String(const char *s)
{
    _size = strlen(s);
    _data = new char[_size + 1];
    _data[_size] = '\0';
    for (int i = 0; i < _size; i++)
    {
        _data[i] = s[i];
    }
}

String String::operator=(const char *s)
{
    delete[] _data;
    _size = strlen(s);
    _data = new char[_size + 1];
    _data[_size] = '\0';
    for (int i = 0; i < _size; i++)
    {
        _data[i] = s[i];
    }
    return *this;
}

bool String::operator==(const String &s) const
{
    if (this->_size != s._size)
        return false;

    bool flag = true;
    for (int i = 0; i < this->_size; i++)
    {
        if (this->_data[i] != s._data[i])
            flag = false;
    }
    return flag;
}

bool String::operator!=(const String &s) const
{
    return !(*this == s);
}

bool String::operator<(const char *s) const
{
    int len = std::min(_size, int(strlen(s)));
    bool flag = false;
    bool res = false;
    for (int i = 0; i < len; i++)
    {
        if (_data[i] == s[i])
            continue;
        flag = true;
        res = Type::charCompare(_data[i], s[i]);
        break;
    }
    if (!flag)
    {
        res = _size < strlen(s);
    }
    return res;
}

bool String::operator<(const String &s) const
{
    return *this < s.data();
}

char &String::operator[](int i)
{
    if (i < 0)
        return _data[i % _size + _size];
    else if (i >= _size)
        return _data[i % _size];
    return _data[i];
}

char *String::data() const
{
    return this->_data;
}

int String::size()
{
    return this->_size;
}

class Device
{
private:
    String name;
    String brand;
    int price;
    int amount;

public:
    Device();
    Device(String name, String brand, int price, int amount);
    bool operator<(const Device &device) const;
};

Device::Device()
{
    name = "";
    brand = "";
    price = 0;
    amount = 0;
}

Device::Device(String name, String brand, int price, int amount)
{
    this->name = name;
    this->brand = brand;
    this->price = price;
    this->amount = amount;
}

bool Device::operator<(const Device &device) const
{
    if (this->brand != device.brand)
        return this->brand < device.brand;
    else if (this->name != device.brand)
        return this->brand < device.brand;
}

template <class T>
class LinkedList
{
private:
    class LinkedListNode
    {
    private:
        T data;
        LinkedListNode *_next;

    public:
        LinkedListNode();
        LinkedListNode(T data, LinkedListNode *_next);
        LinkedListNode *next();
    };
    T *head;
    int _length;

public:
    class Iterator //定义链表迭代器，实现自定义链表遍历方式
    {
    private:
        LinkedListNode *_it;

    public:
        Iterator();
        Iterator(LinkedListNode *it);
        T &operator*();        //*it表示取得it这个指针在链表中指向的值
        Iterator operator++(); //重载++运算符
        bool isNULL();         //判断迭代器是否为空
    };
    LinkedList();
    void insert(T _data);
    void insert(int pos, T data);
    void erase();
    void erase(int pos);
    T &operator[](int pos);
    void reverse(int a, int b);
    int length();
    Iterator begin();
};

template <class T>
LinkedList<T>::Iterator::Iterator()
{
    _it = NULL;
}

template <class T>
LinkedList<T>::Iterator::Iterator(LinkedListNode *it)
{
    this->_it = it;
}

template <class T>
T &LinkedList<T>::Iterator::operator*()
{
    if (_it)
        return _it->_data;
    else
        return shitInt;
}

template <class T>
LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++()
{
    if (_it)
        _it = _it->_next;
    return *this;
}

template <class T>
bool LinkedList<T>::Iterator::isNULL()
{
    return _it == NULL;
}

template <class T>
LinkedList<T>::LinkedList()
{
    _head = NULL;
    _length = 0;
}

int main()
{

    return 0;
}