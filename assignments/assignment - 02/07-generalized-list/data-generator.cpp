#include <iostream>
#include <cstdio>
#include "Random.h"
#include <queue>
const int maxn = 1050;
int n = 20, cnt;
bool used[maxn];
int G[maxn][maxn] = {0};
int inDegree[maxn] = {0}, outDegree[maxn] = {0};
struct GNode
{
    int tag;
    int num;
    int hp;
    int tp;
} GList[maxn];
void printGeneralizedList(int u)
{
    using namespace std;
    if (u == -1)
    {
        cout << ")";
    }
    else if (GList[u].tag == 0)
    {
        cout << u;
        if(GList[u].tp != -1) cout << ", ";
        printGeneralizedList(GList[u].tp);
    }
    else
    {
        cout << "(";
        printGeneralizedList(GList[u].hp);
        if(GList[u].tp != -1) cout << ", ";
        printGeneralizedList(GList[u].tp);
    }
}
int main()
{
    using namespace std;
    cout << "输入一个正整数 n (n <= 1000)，表示广义表的最小节点数." << endl;
    cin >> n;
    queue<int> q;
    q.push(1);
    cnt++;
    while (!q.empty())
    {
        int now = q.front();
        q.pop();
        int numOfChild = Random::randInt(100);
        if (q.empty() && cnt < n)
            numOfChild = Random::randInt(21, 100);
        if (numOfChild <= 20)
            continue;
        else if (numOfChild <= 90)
        {
            int tp = cnt + 1;
            // cout << now << " " << tp << endl;

            // G[now][tp] = 1;
            // outDegree[now]++;
            // inDegree[tp]++;

            if (numOfChild <= 80)
            {
                GList[now].tag = 0;
                GList[now].tp = tp;
                GList[now].hp = -1;
                GList[now].num = now;
            }
            else
            {
                GList[now].tag = 1;
                GList[now].tp = -1;
                GList[now].hp = tp;
                GList[now].num = now;
            }

            q.push(tp);
            GList[tp].tp = -1;
            GList[tp].hp = -1;
            cnt++;
        }
        else
        {
            int tp = cnt + 1;
            int hp = cnt + 2;
            cnt += 2;
            // cout << now << " " << tp << endl;
            // cout << now << " " << hp << endl;

            // G[now][tp] = 1;
            // G[now][hp] = 1;
            // outDegree[now]++;
            // inDegree[tp]++;
            // inDegree[hp]++;

            GList[now].tag = 1;
            GList[now].tp = tp;
            GList[now].hp = hp;
            GList[now].num = now;

            q.push(tp);
            q.push(hp);

            GList[tp].tp = -1;
            GList[tp].hp = -1;
            GList[hp].tp = -1;
            GList[hp].hp = -1;
        }
        if (cnt >= n)
            break;
    }
    cout << "(";
    printGeneralizedList(1);
    cout << endl;
    return 0;
}