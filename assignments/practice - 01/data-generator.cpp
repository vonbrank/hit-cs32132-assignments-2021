#include <iostream>
#include "IO.h"
#include "Random.h"
#include <string>
#include <algorithm>
#include <random>
#include <cmath>

class Node
{
public:
    int time;
    string name;
    bool operator<(const Node &other) const
    {
        return time < other.time || (time == other.time && name < other.name);
    }
};

int main()
{
    IO::outputRedirectToFile("data.txt");
    int countOfWindows = 20;
    int countOfStudents = 5000;
    cout << countOfWindows << endl;
    for (int i = 1; i <= countOfWindows; i++)
    {
        cout << "Window_" << i << endl;
    }
    cout << endl;
    cout << countOfStudents << endl;

    std::default_random_engine e;                   //引擎
    std::normal_distribution<double> n(3600, 1200); //均值, 方差
    // std::vector<unsigned> vals(100);
    // for (std::size_t i = 0; i != 5000; ++i)
    // {
    //     unsigned v = std::lround(n(e)); //取整-最近的整数
    //     if (v < vals.size())
    //         ++vals[v];
    // }

    int currentTime = 0;
    Node a[countOfStudents];
    for (int i = 0; i < countOfStudents; i++)
    {
        a[i].time = (unsigned int)std::lround(n(e));
        while (a[i].time < 0 || a[i].time > 7200)
            a[i].time = (unsigned int)std::lround(n(e));
        // a[i].time = std::lround(n(e));
        a[i].name = "";
    }
    sort(a, a + countOfStudents);
    for (int i = 0; i < countOfStudents; i++)
    {
        cout << a[i].time << " "
             << "Student_" << i + 1 << endl;
    }
    return 0;
}