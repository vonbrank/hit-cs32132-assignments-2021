#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector
{
private:
    T *data;
    int _size;
    int _capacity;
    void resize()
    {
        if (_size == _capacity)
        {
            T *cache = new T[_size * 2];
            _capacity = _size * 2;
            for (int i = 0; i < _size; i++)
            {
                cache[i] = data[i];
            }
            delete[] data;
            data = cache;
        }
        else if (_size < _capacity / 4 && _capacity >= 4)
        {
            T *cache = new T[_capacity / 4];
            _capacity /= 4;
            for (int i = 0; i < _size; i++)
            {
                cache[i] = data[i];
            }
            delete[] data;
            data = cache;
        }
    }
    void resize(int _size)
    {
        if (_size <= this->_capacity)
            return;
        while (this->_capacity < _size)
            this->_capacity *= 2;
        T *cache = new T[this->_capacity];
        for (int i = 0; i < this->_size; i++)
        {
            cache[i] = data[i];
        }
        delete[] data;
        data = cache;
    }

public:
    Vector()
    {
        data = new T[1];
        _size = 0;
        _capacity = 1;
    }
    Vector(int _size)
    {
        data = new T[_size * 2];
        this->_size = _size;
        this->_capacity = _size * 2;
    }
    ~Vector()
    {
        delete[] data;
    }
    void pushBack(T o)
    {
        resize();
        data[_size++] = o;
    }
    void update(int i, T o)
    {
        if (i < _size)
        {
            if (i < 0)
                i = 0;
            data[i] = o;
        }
        else
        {
            resize(i + 1);
            _size = i + 1;
            data[i] = o;
        }
        resize(i + 1);
    }
    void popBack()
    {
        _size--;
        resize();
    }
    int size()
    {
        return _size;
    }
    int capacity()
    {
        return _capacity;
    }
    T &operator[](int i)
    {
        if (i < 0)
            i = 0;
        if (i >= _size)
            i = _size - 1;
        return data[i];
    }
    void clear()
    {
        _size = 0;
    }
};

#endif