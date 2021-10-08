#include <iostream>
#include <cstdio>
#include <climits>
#include <functional>
#include <vector>
#include "Type.h"

int main()
{
    using namespace std;
    double d = 1.234;
    vector<function<int(int, int)>> f;

    auto lambda = [](double d, int n)
    {
        string str = to_string(d);
        return str.substr(0, str.find_first_of(".") + n + 1);
    };
    cout << lambda(d, 2) << endl;
    // cout << LLONG_MAX << endl;
    return 0;
}
