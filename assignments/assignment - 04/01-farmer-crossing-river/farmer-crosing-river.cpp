/**************************************************************************

Author: 120L021403

Date: 2021-10-27

Description: HIT-数据结构与算法2021-4.1节-农夫过河问题

Note: 标注"//核心代码"的地方表示核心方法

运行此代码即能输出所有解决方案的文字描述


**************************************************************************/

#include <iostream>

class FarmerCrossingRiver
{
private:
    int now[(1 << 6)];
    bool vis[(1 << 6)];
    bool flag;
    int count;
    int getBit(int x, int pos)
    {
        return !((x & (1 << pos)) == 0);
    }
    void setBit(int &x, int pos, int value)
    {
        if (value)
            x |= (1 << pos);
        else
            x &= ~(1 << pos);
    }
    void showBit(int x)
    {
        for (int i = 0; i <= 3; i++)
        {
            std::cout << (getBit(x, i)) << " ";
        }
        std::cout << std::endl;
    }
    bool check(int state)
    {
        if (state & 1)
        {
            if (getBit(state, 1) == getBit(state, 2) && getBit(state, 1) == 0)
                return false;
            if (getBit(state, 2) == getBit(state, 3) && getBit(state, 2) == 0)
                return false;
            return true;
        }
        else
        {
            if (getBit(state, 1) == getBit(state, 2) && getBit(state, 1) == 1)
                return false;
            if (getBit(state, 2) == getBit(state, 3) && getBit(state, 2) == 1)
                return false;
            return true;
        }
        return false;
    }
    bool checkSuccess(int state)
    {
        for (int i = 0; i <= 3; i++)
        {
            if (getBit(state, i) == 0)
                return false;
        }
        return true;
    }
    /*
    vis     0               1               2               3
            person          vegetable       sheep           wolf
    */
    void dfs(int depth) //核心代码
    {
        if (!check(now[depth]))
            return;
        // showBit(now[depth]);
        if (checkSuccess(now[depth]))
        {
            count++;
            std::cout << "Solution " << count << " Founded: " << std::endl;
            for (int i = 2; i <= depth; i++)
            {
                int item = -1;
                for (int j = 1; j <= 3; j++)
                {
                    if (getBit(now[i], j) != getBit(now[i - 1], j))
                    {
                        item = j;
                        break;
                    }
                }
                if (getBit(now[i], 0))
                {
                    std::cout << "Farmer goes across the river with ";
                }
                else
                {
                    std::cout << "Farmer goes back across the river with ";
                }
                switch (item)
                {
                case -1:
                    std::cout << "nothing";
                    break;
                case 1:
                    std::cout << "vegetable";
                    break;
                case 2:
                    std::cout << "sheep";
                    break;
                case 3:
                    std::cout << "wolf";
                    break;
                }
                std::cout << "." << std::endl;
                // showBit(now[i]);
            }
            std::cout << std::endl;
            // exit(0);
            return;
        }
        for (int i = 1; i <= 3; i++)
        {
            if (getBit(now[depth], 0) != getBit(now[depth], i))
                continue;
            now[depth + 1] = now[depth];
            setBit(now[depth + 1], 0, getBit(now[depth + 1], 0) ^ 1);
            setBit(now[depth + 1], i, getBit(now[depth + 1], i) ^ 1);
            if (vis[now[depth + 1]])
                continue;
            vis[now[depth + 1]] = true;
            dfs(depth + 1);
            vis[now[depth + 1]] = false;
        }

        now[depth + 1] = now[depth];
        setBit(now[depth + 1], 0, getBit(now[depth + 1], 0) ^ 1);
        if (!vis[now[depth + 1]])
        {
            vis[now[depth + 1]] = true;
            dfs(depth + 1);
            vis[now[depth + 1]] = false;
        }
    }

public:
    FarmerCrossingRiver()
    {
        count = 0;
        for (int i = 0; i < (1 << 6); i++)
        {
            vis[i] = false;
            now[i] = 0;
        }
        flag = false;
    }
    void run()
    {
        dfs(1);
    }
};

int main()
{
    FarmerCrossingRiver farmerCrossingRiver;
    farmerCrossingRiver.run();
    return 0;
}