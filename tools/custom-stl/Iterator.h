#ifndef ITERATOR_H
#define ITERATOR_H

class Iterator
{
protected:
    void *_it;

public:
    Iterator();
    virtual ~Iterator();
    virtual int &operator*();
    virtual Iterator operator++();
    virtual bool isNULL();
};

#endif