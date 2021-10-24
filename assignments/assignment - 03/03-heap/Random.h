#ifndef RANDOM_H
#define RANDOM_H
#include <iostream>
#include <ctime>

class Random
{
public:
    static int randInt()
    {
        static int seed = int(time(NULL) * 48271LL % 2147483647);
        return seed = int(seed * 48271LL % 2147483647);
    }
    static int randInt(int n)
    {
        return randInt() % (n + 1);
    }
    static int randInt(int a, int b)
    {
        return a + randInt() % (b - a + 1);
    }
    static long long randLongLong()
    {
        return ((long long)(randInt()) << 32 ) + randInt();
    }
    static void shuffle(int *a, int length)
    {
        for(int i=0; i<length; i++)
        {
            int rand = randInt(i, length - 1);
            std::swap(*(a + i), *(a + rand));
        }
    }
};
#endif