#include <stdio.h>

struct Team
{
    int id;
    int score;
};

void TeamConstructor(struct Team *team, int id, int score)
{
    team->id = id;
    team->score = score;
}

int TeamCompareTo(struct Team *team, struct Team *o)
{
    return team->score > o->score;
}

void TeamMergeSortCore(struct Team *teamArray, int begin, int end, struct Team *cache)
{
    if (begin == end)
        return;
    int mid = (begin + end) >> 1;
    intMergeSortCore(teamArray, begin, mid, cache);
    intMergeSortCore(teamArray, mid + 1, end, cache);
    int i = begin, j = mid + 1, k = 0;
    while (i <= mid || j <= end)
    {
        if (i > mid)
        {
            while (j <= end)
            {
                cache[k++] = teamArray[j++];
            }
        }
        else if (j > end)
        {
            while (i <= mid)
            {
                cache[k++] = teamArray[i++];
            }
        }
        else
        {
            if (teamCompareTo(&teamArray[i], &teamArray[j]))
            {
                cache[k++] = teamArray[i++];
            }
            else
            {
                cache[k++] = teamArray[j++];
            }
        }
    }
    for (i = begin, j = 0; i <= end; i++, j++)
    {
        teamArray[i] = cache[j];
    }
}

void TeamMergeSort(struct Team *teamArray, int begin, int end)
{
    struct Team cache[end - begin];
    TeamMergeSortCore(teamArray, begin, end, cache);
}

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

int main()
{
    int n;
    scanf("%d", &n);
    int a[n + 10][n + 10], score[n + 10];
    for (int i = 1; i <= n; i++)
    {
        score[i] = 0;
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &a[i][j]);
            score[i] += a[i][j];
        }
    }

    return 0;
}