#include <iostream>
#include <fstream>

void toHex(char *str)
{
    using namespace std;
    fstream fout;
    fout.open("hex.txt", ofstream::app);
    static int count = 0;
    count++;
    char hex[17] = "0123456789ABCDEF";
    int b[4] = {8, 4, 2, 1};
    int ans = 0;
    for (int i = 0; i < 4; i++)
    {
        ans += (str[i] - '0') * b[i];
    }
    fout << hex[ans];
    if (count % 2 == 0)
        fout << " ";
    if (count % 32 == 0)
        fout << std::endl;
}

int main()
{
    using namespace std;
    fstream fin;
    fin.open("binary.txt");
    fstream fout;
    fout.open("hex.txt", ios::out);
    // fout << '\n';
    fout.close();
    char x;
    int count = 0;
    char str[4];
    while (fin >> x)
    {
        str[count] = x;
        count++;
        if (count >= 4)
        {
            count = 0;
            toHex(str);
        }
    }
    while (count < 4)
    {
        str[count] = '0';
        count++;
    }
    toHex(str);
    return 0;
}