#include <stdio.h>

void intMergeSortCore(int *intArray, int begin, int end, int *cache)
{
    if (begin == end)
        return;
    int mid = (begin + end) >> 1;
    intMergeSortCore(intArray, begin, mid, cache);
    intMergeSortCore(intArray, mid + 1, end, cache);
    int i = begin, j = mid + 1, k = 0;
    while (i <= mid || j <= end)
    {
        if (i > mid)
        {
            while (j <= end)
            {
                cache[k++] = intArray[j++];
            }
        }
        else if (j > end)
        {
            while (i <= mid)
            {
                cache[k++] = intArray[i++];
            }
        }
        else
        {
            if (intArray[i] < intArray[j])
            {
                cache[k++] = intArray[i++];
            }
            else
            {
                cache[k++] = intArray[j++];
            }
        }
    }
    for (i = begin, j = 0; i <= end; i++, j++)
    {
        intArray[i] = cache[j];
    }
}

void intMergeSort(int *intArray, int begin, int end)
{
    int cache[end - begin];
    intMergeSortCore(intArray, begin, end, cache);
}

// int a[100500];
int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    int a[n + 10];
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        // printf("%d ", i);
    }
    intMergeSort(a, 1, n);
    for (int i = 1; i <= n; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}