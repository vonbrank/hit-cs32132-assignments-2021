/**************************************************************************

Author: 120L021403

Date: 2021-10-04

Description: HIT-数据结构与算法2021-2.7节-实现广义表字符串的解析和数据结构的深度拷贝

Note: 标注"//核心代码的地方表示核心方法"

输入格式：

第一行输入一个字符串，表示广义表。

广义表的总节点数不大于1000，无递归结构、无共享节点，且应该在一行内输入完成。

形如：(1, (3, 4, 5, (8), 7, 9, 10, 11, 12, 13, 14, (17, 19), 16, 18, 20))。

不合法的输入可能导致ub。

输出格式：

读入字符串后将其作为广义表类 GeneralizedList 下的实例 gll 的构造参数，构造广义表。

接着创建 gll2 实例进行无参构造，然后调用 void deepCopyFrom(const GeneralizedList &g) 方法对 gll 进行深度拷贝。

最后调用 gll2 的 toString() 方法输出其广义表字符串，其形式应和输入等价，并有更标准的格式。

样例：

输入1：

(1, (3, 4, 5, (8), 7, 9, 10, 11, 12, 13, 14, (17, 19), 16, 18, 20))

输出1：

(1, (3, 4, 5, (8), 7, 9, 10, 11, 12, 13, 14, (17, 19), 16, 18, 20))


输入2：

(1, 2, 3, 4, 5, 6, 7, (9, (11, 12, 13, 14, 15, (17, (20, ), 19),),  )     )

输出2：

(1, 2, 3, 4, 5, 6, 7, (9, (11, 12, 13, 14, 15, (17, (20), 19))))


**************************************************************************/


#include <iostream>
#include <string>
#include "Type.h"

class GeneralizedListNode
{
private:
    int tag;
    union
    {
        int data;
        GeneralizedListNode* hp;
    };
    GeneralizedListNode *tp;
    friend class GeneralizedList;

public:
    GeneralizedListNode(int data, GeneralizedListNode* tp)
    {
        this->tag = 0;
        this->data = data;
        this->tp = tp;
    }
    GeneralizedListNode(GeneralizedListNode *hp, GeneralizedListNode* tp)
    {
        this->tag = 1;
        this->hp = hp;
        this->tp = tp;

    }
};

class GeneralizedList
{
private:
    std::string generalizedListString;
    GeneralizedListNode *head;
    int getType(int l, int r)
    {
        for(int i=l; i<=r; i++)
        {
            if(generalizedListString[i] == '(') return 1;
        }
        return 0;
    }
    int getNextPos(int start)
    {
        int cnt = 0;
        for(int i = start; ; i++)
        {
            if(generalizedListString[i] == '(') cnt++;
            if(generalizedListString[i] == ')') cnt--;
            if(cnt == 0 && (generalizedListString[i+1] == ',' || generalizedListString[i+1] == ')' || generalizedListString[i+1] == ' '))
            {
                return i;
            }
            if(i >= generalizedListString.size()) return -1;
        }
        return - 1;
    }
    GeneralizedListNode* build(int l, int r)
    {
        GeneralizedListNode *headNode = NULL;
        GeneralizedListNode *preNode = NULL;
        GeneralizedListNode *nowNode;
        int start = l, end = r;
        while(generalizedListString[start] != '(') start++;
        start++;
        while(generalizedListString[end] != ')') end--;
        end--;
        bool flag = true;
        for(int i=start; i<=end; i++)
        {
            if(generalizedListString[i] != ' ') flag = false;
            
        }
        if(flag) return NULL;
        for(int i=start; i<=end; )
        {   
            while(!(generalizedListString[i] == '(' || Type::isDigit(generalizedListString[i])))
            {
                i++;    
                if(i > end) return headNode;
            } 
            int nextPos = getNextPos(i);
            int type = getType(i, nextPos);
            if(type == 0) 
            {
                int num = 0;
                for(int j=i; j<=nextPos; j++)
                {
                    num *= 10;
                    num += int(generalizedListString[j] - '0');
                }
                // std::cout << num << std::endl;
                nowNode = new GeneralizedListNode(num, NULL);
                
            }
            else
            {
                nowNode = new GeneralizedListNode(build(i, nextPos), NULL);
            }

            if(preNode) preNode->tp = nowNode;
            else headNode = nowNode;
            preNode = nowNode;
            i = nextPos + 1;

        }
        return headNode;
    }
    void deepCopy(GeneralizedListNode *const &s, GeneralizedListNode *&t)
    {
        if(s == NULL)
        {
            t = NULL;
            return;
        }
        if(s->tag == 0)
        {
            t = new GeneralizedListNode(s->data, s->tp);
            deepCopy(s->tp, t->tp);
        }
        else
        {
            t = new GeneralizedListNode(s->hp, s->tp);
            deepCopy(s->hp, s->hp);
            deepCopy(s->tp, s->tp);
        }
    }
    void deleteNode(GeneralizedListNode *rt)
    {
        if(rt == NULL) return;
        if(rt->tag == 0)
        {
            deleteNode(rt->tp);
        }
        else
        {
            deleteNode(rt->hp);
            deleteNode(rt->tp);
        }
        delete rt;
    }
    void generateStringCore(GeneralizedListNode *u)
    {
        if(u == NULL)
        {
            generalizedListString += ")";
        }
        else if(u->tag == 0)
        {
            char s[32];
            sprintf(s, "%d", u->data);
            generalizedListString += s;
            if(u->tp) generalizedListString += ", ";
            generateStringCore(u->tp);
        }
        else 
        {
            generalizedListString += "(";
            generateStringCore(u->hp);
            if(u->tp) generalizedListString += ", ";
            generateStringCore(u->tp);
        }
    }
    void generateString()
    {
        generalizedListString = "(";
        generateStringCore(head);
    }
public:
    GeneralizedList()
    {
        generalizedListString = "";
        head = NULL;
    }
    GeneralizedList(std::string generalizedListString)
    {
        this->generalizedListString = generalizedListString;
        head = build(0, generalizedListString.size() - 1);
        generateString();
    }

    void deepCopyFrom(const GeneralizedList &g)
    {
        deleteNode(head);
        deepCopy(g.head, head);
        generateString();
    }
    std::string toString()
    {
        return this->generalizedListString;
    }

};

int main()
{
    std::cout << "第一行输入一个字符串，表示广义表。" << std::endl;
    std::cout << "形如：(1, (3, 4, 5, (8), 7, 9, 10, 11, 12, 13, 14, (17, 19), 16, 18, 20))。" << std::endl;
    std::cout << "不合法的输入可能导致ub。" << std::endl;
    std::string generalizedListString;
    std::getline(std::cin, generalizedListString);
    GeneralizedList gll(generalizedListString);
    GeneralizedList gll2;
    gll2.deepCopyFrom(gll);
    std::cout << gll2.toString() << std::endl;
    return 0;
}
