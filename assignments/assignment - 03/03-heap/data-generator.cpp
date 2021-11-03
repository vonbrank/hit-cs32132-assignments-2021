#include <iostream>
#include <fstream>
#include "Random.h"

const int n = 10;

const int maxLevel = 1000;

int main()
{
    using namespace std;
    int num, level;
    fstream fout;
    fout.open("input.txt");
    for (int i = 1; i <= n; i++)
    {
        fout << i << " " << Random::randInt(0, maxLevel) << endl;
    }
    return 0;
}