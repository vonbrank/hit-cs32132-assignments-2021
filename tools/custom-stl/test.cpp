#include <iostream>
#include <cstdio>
#include "Stack.h"
using namespace std;

int main()
{
    StaticStack<int> stack(100);
    int n = 10;
    for (int i = 1; i <= n; i++)
    {
        stack.createStack();
    }
    for (int i = 1; i <= 50; i++)
    {
        stack.push(i % 10, i);
    }
    for (int i = 0; i < stack.numberOfStack(); i++)
    {
        while (!stack.empty(i))
        {
            printf("%d ", stack.top(i));
            stack.pop(i);
        }
        printf("\n");
    }
    return 0;
}