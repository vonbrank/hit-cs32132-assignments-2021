#include <iostream>
#include <random>
#include <string>

int main()
{
    using namespace std;
    int op;
    string str;
    do
    {
        cin >> op;
        char c;
        while((c = getchar()) != '\n')
        {
            cout << c << endl;
        }
        // cin.clear();
        cout << op << endl;
        cin >> str;

    } while(op != -1);
    return 0;
}
