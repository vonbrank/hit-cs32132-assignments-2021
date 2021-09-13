#include <iostream>
#include <cstdio>
#include <ctime>
char *path;
FILE *fp;
inline int intRangeRand()
{
    static int seed = time(NULL);
    return seed = int(seed * 48271LL % 2147483647);
}

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

void task_01()
{
    int n = 100;
    int len = 10;
    printf("输入字符串的个数n和最大长度len，以空格分隔：\n");
    scanf("%d %d", &n, &len);
    if (len < 1)
        len = 1;
    fprintf(fp, "%d %d\n", n, len);
    for (int i = 1; i <= n; i++)
    {
        fprintf(fp, "%s\n", getRandString(len));
    }
}

void task_02()
{
    int n = 100;
    int maxNumer = 10000;
    printf("输入数字的个数n及其最大值maxNumber，以空格分隔：\n");
    scanf("%d %d", &n, &maxNumer);
    fprintf(fp, "%d\n", n);
    for (int i = 1; i <= n; i++)
    {
        double tmp = double(intRangeRand());
        tmp = tmp / 100000 - (int)tmp / 100000;
        fprintf(fp, "%lf ", (intRangeRand() % maxNumer + 1 + tmp) * (intRangeRand() % 2 ? 1.0 : -1.0));
    }
}

void task_03()
{

    int n = 6;
    printf("输入队伍个数，最少为2支：\n");
    scanf("%d", &n);
    if (n <= 1)
        n = 2;
    fprintf(fp, "%d\n", n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            int u, v, w;
            u = i;
            v = j;
            if (intRangeRand() % 2)
                std::swap(u, v);
            w = 1;
            fprintf(fp, "%d %d\n", u, v);
        }
    }
}

int main()
{

    path = "input.txt";
    fp = fopen(path, "w+");

    int op;

    printf("1 第1题\n");
    printf("2 第2题\n");
    printf("3 第3题\n");
    printf("输入选择生成数据的题号：\n");
    scanf("%d", &op);
    if (op < 1)
        op = 1;
    if (op > 3)
        op = 3;
    if (op == 1)
        task_01();
    if (op == 2)
        task_02();
    if (op == 3)
        task_03();
    printf("成功生成第%d题的测试数据，已保存至当前文件夹下%s中.\n", op, path);
    fclose(fp);
    return 0;
}