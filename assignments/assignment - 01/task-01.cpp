#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstring>
using namespace std;

inline int intRangeRand()
{
    static int seed = time(NULL);
    return seed = int(seed * 48271LL % 2147483647);
}

class CustomString
{
private:
    char *val;
    int len;
    static void mergeSort(CustomString *customStringArray, int begin, int end, CustomString *cache)
    {
        if (begin == end)
            return;
        int mid = (begin + end) >> 1;
        mergeSort(customStringArray, begin, mid, cache);
        mergeSort(customStringArray, mid + 1, end, cache);
        int i = begin, j = mid + 1, k = 0;
        while (i <= mid || j <= end)
        {
            if (i > mid)
            {
                while (j <= end)
                {
                    cache[k++] = customStringArray[j++];
                }
            }
            else if (j > end)
            {
                while (i <= mid)
                {
                    cache[k++] = customStringArray[i++];
                }
            }
            else
            {
                if (customStringArray[i] < customStringArray[j])
                {
                    cache[k++] = customStringArray[i++];
                }
                else
                {
                    cache[k++] = customStringArray[j++];
                }
            }
        }
        for (int i = begin, j = 0; i <= end; i++, j++)
        {
            customStringArray[i] = cache[j];
        }
    }

public:
    CustomString()
    {
        this->val = new char[1];
        val[0] = '\0';
        this->len = 0;
    }
    CustomString(char *val, int len)
    {
        char *cache = new char[len + 1];
        for (int i = 0; i < len; i++)
            cache[i] = val[i];
        cache[len] = '\0';
        this->val = cache;
        this->len = len;
    }
    void setValue(char *value)
    {
        delete[] this->val;
        this->len = strlen(value);
        this->val = new char[this->len + 1];
        for (int i = 0; i < this->len; i++)
        {
            this->val[i] = value[i];
        }
        this->val[len] = '\0';
    }
    bool operator<(const CustomString &o) const
    {
        bool result = false;
        int len = min(this->len, o.len);
        bool flag = true;
        for (int i = 0; i < len; i++)
        {
            if (this->val[i] == o.val[i])
                continue;
            if (isalpha(this->val[i]) && isalpha(o.val[i]))
            {
                if (tolower(this->val[i]) == tolower(o.val[i]))
                {
                    result = this->val[i] < o.val[i];
                }
                else
                {
                    result = tolower(this->val[i]) < tolower(o.val[i]);
                }
            }
            else if (isdigit(this->val[i]) && isdigit(o.val[i]))
            {
                result = this->val[i] < o.val[i];
            }
            else
            {
                result = isdigit(this->val[i]);
            }
            flag = false;
            break;
        }
        if (flag)
            result = this->len < o.len;
        return result;
    }
    char *toString()
    {
        return this->val;
    }

    static void mergeSort(CustomString *customStringArray, int begin, int end)
    {
        CustomString cache[end - begin];
        mergeSort(customStringArray, begin, end, cache);
    }
};

char *getRandString(int maxLen)
{
    int len = intRangeRand() % maxLen + 1;
    char *result = new char[len + 1];
    for (int i = 0; i < len; i++)
    {
        int charType = intRangeRand() % 3;
        if (charType == 0)
            result[i] = intRangeRand() % 10 + '0';
        else if (charType == 1)
            result[i] = intRangeRand() % 26 + 'a';
        else if (charType == 2)
            result[i] = intRangeRand() % 26 + 'A';
    }
    result[len] = '\0';
    return result;
}

int main()
{
    CustomString customStringList[110];
    int n, len;
    scanf("%d %d", &n, &len);
    for (int i = 1; i <= n; i++)
    {
        char cache[len + 10];
        scanf("%s", cache);
        customStringList[i].setValue(cache);
        // printf("%s\n", customStringList[i].toString());
    }
    printf("\n");
    printf("output:\n");
    printf("------------\n");
    CustomString::mergeSort(customStringList, 1, n);
    for (int i = 1; i <= n; i++)
    {
        printf("%s\n", customStringList[i].toString());
    }
    return 0;
}