/**************************************************************************

Author: 120L021403

Date: 2021-09-27

Description: HIT-数据结构与算法2021-2.4节-实现共享栈

Note: 共享栈容器的声明和实现存放在 Stack.h 里

输入格式：

第一行三个数，n, m, k，表示共享栈的个数，存储池大小，以及指令条数。

接下来 k 每行一条命令，有三种命令：

1 x y 表示向 x 号栈压入元素 y ，的范围为[0, n - 1]

2 x 表示输出 x 号栈的栈顶元素。

3 x 表示弹出 x 号栈的栈顶元素，空栈不做任何操作。

输出格式：

对于每个 2 操作，输出结果，空栈栈顶返回0。

全部操作结束后输出 n 行，表示[0, n - 1]每个栈从栈顶到栈底的所有元素。

样例：

输入：
8 39 39
3 5
3 0
3 0
1 7 105
1 2 40
2 2
3 5
3 5
1 2 98
1 1 91
1 3 47
1 6 106
3 0
3 6
2 1
2 5
1 4 113
3 3
2 0
1 5 20
1 3 120
2 1
1 0 114
1 6 42
1 7 54
2 3
2 5
1 7 5
1 3 101
1 2 100
2 6
1 4 7
1 5 122
1 0 48
2 6
1 2 77
1 5 122
1 7 121
1 0 112



输出：
40
91
0
0
91
120
20
42
42
0: 112 48 114 
1: 91 
2: 77 100 98 40 
3: 101 120 
4: 7 113 
5: 122 122 20 
6: 42 
7: 121 5 54 105 


**************************************************************************/

#include <iostream>
#include <cstdio>
#include "Stack.h"

int main()
{
    freopen("out", "w", stdout);
    printf("输入输出格式请参考源文件上方注释\n");
    printf("建议使用data-generator.cpp生成数据至input.txt\n");
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    StaticStack<int> stack(m);
    for (int i = 1; i <= n; i++)
    {
        stack.createStack();
    }
    for (int i = 1; i <= k; i++)
    {
        int op;
        scanf("%d", &op);
        if (op == 1)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            stack.push(x, y);
        }
        else if (op == 2)
        {
            int x;
            scanf("%d", &x);
            printf("%d\n", stack.top(x));
        }
        else if (op == 3)
        {
            int x;
            scanf("%d", &x);
            stack.pop(x);
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%d: ", i);
        while (!stack.empty(i))
        {
            printf("%d ", stack.top(i));
            stack.pop(i);
        }
        printf("\n");
    }
}