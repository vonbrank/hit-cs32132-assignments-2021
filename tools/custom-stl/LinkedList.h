#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <cstdio>
#include <exception>
#include <stdexcept>
#include "Iterator.h"

template <class T>
class LinkedList
{
public:
    virtual void insert(const T &_data) = 0;
    virtual void insert(int pos, const T &_date) = 0;
    virtual T &get(int pos);
    virtual void erase() = 0;
    virtual void erase(int pos) = 0;
    virtual int length() const = 0;
};

template <class T>
class LinkedListString : public LinkedList
{
private:
    class Node
    {
    private:
        T _data;
        Node *next;

    public:
        Node(const T &_data, Node *_next);
        T &data();
        Node *&next();
    };

    class Iterator : public ::Iterator
    {
    };

    LinkedList *_head;
    int _length;

public:
    static int index(const LinkedListString &s, const LinkedListString &t);
    static LinkedListString subString(const LinkedListString &s, int m, int n);
};

template <class T>
bool LinkedListString<T>::Iterator::isNULL()
{
}

template <class T>

template <class T>
void LinkedList<T>::insert(const T &_data)
{
}

template <class T>
void LinkedList<T>::insert(int pos, const T &_data)
{
}

template <class T>
void LinkedList<T>::erase()
{
}

template <class T>
void LinkedList<T>::erase(int pos)
{
}

template <class T>
int LinkedList<T>::length() const
{
}

template <class T>
int LinkedListString<T>::index(const LinkedListString &s, const LinkedListString &t)
{
}

template <class T>
LinkedListString<T> LinkedListString<T>::subString(const LinkedListString &s, int m, int n)
{
}
#endif
