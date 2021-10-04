#ifndef STRING_CPP
#define STRING_CPP

#include <iostream>
#include <cstdio>
#include <cstring>
#include "Type.h"

class String
{
private:
    int _size;
    char *_data;
    void resize();
public:
    String();
    String(const char *s);
    String operator=(const char *s);
    bool operator<(const char *s);
    bool operator<(String s);
    char *data() const;
    int size();
    void push(char c);
    void pop();
    void shift(char c);
    void unshift();
};

void String::resize()
{
    
}

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

bool String::operator<(const char *s)
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

bool String::operator<(String s)
{
    return *this < s.data();
}

char *String::data() const
{
    return this->_data;
}

int String::size()
{
    return this->_size;
}

void String::push(char c)
{
    
}

#endif