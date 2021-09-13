#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
const int maxn = 100;
int min(int a, int b)
{
    return a < b ? a : b;
}
struct MyString
{
    char *val;
    int len;
};

void myStringConstructor(struct MyString *myString, char *val, int len)
{
    char *tmp = (char *)malloc((len + 1) * sizeof(char));
    for (int i = 0; i < len; i++)
        tmp[i] = val[i];
    tmp[len] = '\0';
    myString->val = tmp;
    myString->len = len;
}

int myStringCompareTo(struct MyString *myString, struct MyString o)
{
    int res = 0;
    int len = min(myString->len, o.len);
    int flag = 1;
    for (int i = 0; i < len; i++)
    {
        if (myString->val[i] == o.val[i])
            continue;
        if (isalpha(myString->val[i]) && isalpha(o.val[i]))
        {
            if (tolower(myString->val[i]) == tolower(o.val[i]))
            {
                res = myString->val[i] < o.val[i];
            }
            else
            {
                res = tolower(myString->val[i]) < tolower(o.val[i]);
            }
        }
        else if (isdigit(myString->val[i]) && isdigit(o.val[i]))
        {
            res = tolower(myString->val[i]) < tolower(o.val[i]);
        }
        else
        {
            res = isdigit(myString->val[i]);
        }
        flag = 0;
        break;
    }
    if (flag)
        res = myString->len < o.len;
    return res != 0;
}
char *myStringToString(struct MyString *myString)
{
    return myString->val;
}

void myStringMergeSort(struct MyString *myStringArray, int begin, int end)
{
    if (begin == end)
        return;
    struct MyString tmp[end - begin];
    int mid = (begin + end) >> 1;
    myStringMergeSort(myStringArray, begin, mid);
    myStringMergeSort(myStringArray, mid + 1, end);
    int i = begin, j = mid + 1, k = 0;
    while (i <= mid || j <= end)
    {
        if (i > mid)
        {
            while (j <= end)
            {
                tmp[k++] = myStringArray[j++];
            }
        }
        else if (j > end)
        {
            while (i <= mid)
            {
                tmp[k++] = myStringArray[i++];
            }
        }
        else
        {
            if (myStringCompareTo(&myStringArray[i], myStringArray[j]))
            {
                tmp[k++] = myStringArray[i++];
            }
            else
            {
                tmp[k++] = myStringArray[j++];
            }
        }
    }
    for (int i = begin, j = 0; i <= end; i++, j++)
    {
        myStringArray[i] = tmp[j];
    }
}

int main()
{
    struct MyString myStringArray[100];
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        char tmp[100];
        scanf("%s", tmp);
        myStringConstructor(&myStringArray[i], tmp, strlen(tmp));
    }
    myStringMergeSort(myStringArray, 1, n);
    for (int i = 1; i <= n; i++)
    {
        printf("%s ", myStringArray[i].val);
    }
    return 0;
}