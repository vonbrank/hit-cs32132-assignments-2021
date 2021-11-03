/**************************************************************************

Author: 120L021403

Date: 2021-10-17

Description: HIT-数据结构与算法2021-3.3节-二叉堆

Note: 标注"//核心代码"的地方表示核心方法

输入格式：

本题要求从文件输入，设文件 task.in 中存放了仿真进程服务请求。

输入若干行，每行两个整数，分别表示进程号和优先级。

输出格式：

一行，优先级从高到低依次输出进程编号，对于优先级相同的，编号小的排在前面。

样例：

输入1：

1 30
2 20
3 40
4 20
5 0

输出1：

3 1 2 4 5


**************************************************************************/

#include <iostream>
#include <vector>
#include <fstream>

class Task
{
private:
    int num, level;
    friend std::ostream &operator<<(std::ostream &os, const Task &t)
    {
        os << "num: " << t.num << ", " << "level: " << t.level;
        return os;
    }
    friend std::fstream &operator<<(std::fstream &fs, const Task &t)
    {
        fs << t.num;
        return fs;
    }

public:
    Task() : num(0), level(0) {}
    Task(int num, int level) : num(num), level(level) {}
    bool operator<(const Task &t) const
    {
        if (level != t.level)
            return level < t.level;
        else
            return num > t.num;
    }
};

template <class T> //核心代码
class PropertyQueue
{
private:
    std::vector<T> _data;

public:
    PropertyQueue()
    {
        T t;
        _data.push_back(t);
    }
    void push(T t)
    {
        _data.push_back(t);
        int now = _data.size() - 1;
        while (!(now == 1 || _data[now] < _data[now >> 1]))
        {
            std::swap(_data[now], _data[now >> 1]);
            now >>= 1;
        }
    }
    void pop()
    {
        if (_data.size() == 1)
            return;
        int now = _data.size() - 1;
        std::swap(_data[1], _data[now]);
        _data.pop_back();
        if (_data.size() == 1)
            return;
        now = 1;
        while (true)
        {
            if ((now << 1) < _data.size())
            {
                int next = now << 1;
                if ((now << 1 | 1) < _data.size() && _data[now << 1] < _data[now << 1 | 1])
                    next = now << 1 | 1;
                if (_data[now] < _data[next])
                    std::swap(_data[now], _data[next]);
                else
                    break;
                now = next;
            }
            else
            {
                break;
            }
        }
    }
    bool empty()
    {
        return _data.size() == 1;
    }
    int size()
    {
        return _data.size() - 1;
    }
    T front()
    {
        return _data[1];
    }
};

int main()
{
    using namespace std;
    fstream fin;
    fin.open("input.txt");
    // fstream fout;
    // fout.open("task.out");
    int x, level;
    PropertyQueue<Task> queue;
    while (fin >> x >> level)
    {
        Task t(x, level);
        queue.push(t);
    }
    while (!queue.empty())
    {
        cout << queue.front() << endl;
        queue.pop();
    }
    return 0;
}