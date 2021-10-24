#include <iostream>
#include "Random.h"

int main()
{
    using namespace std;

    int a[110];
    for(int i=1; i<=3; i++)
    {
        a[i] = i;
    }
    Random::shuffle(a + 1, 3);
    for(int i=1; i<= 3; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}
