#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Type.h"
using namespace std;

class HomeAppliance
{
private:
    string name;
    string brand;
    double price;
    int count;

public:
    HomeAppliance()
    {
        this->name = "";
        this->brand = "";
        this->price = 0;
        this->count = 0;
    }
    HomeAppliance(string name, string brand, double price, int count)
    {
        this->name = name;
        this->brand = brand;
        this->price = price;
        this->count = count;
    }
    bool operator<(const HomeAppliance &homeAppliance) const
    {
        if (this->brand == homeAppliance.brand)
        {
            return this->name < homeAppliance.name;
        }
        else
        {
            return this->brand < homeAppliance.brand;
        }
        return false;
    }
    bool operator==(const HomeAppliance &homeAppliance) const
    {
        return this->name == homeAppliance.name && this->brand == homeAppliance.brand;
    }
    string getName()
    {
        return this->name;
    }
    string getBrand()
    {
        return this->brand;
    }
    double getPrice()
    {
        return this->price;
    }
    int getCount()
    {
        return this->count;
    }
    void setCount(int count)
    {
        this->count = count;
    }
    string toString()
    {
        string str;
        auto doubleToString = [](double d, int n)
        {
            string str = to_string(d);
            return str.substr(0, str.find_first_of(".") + n + 1);
        };
        str += "name: " + this->name + "\n";
        str += "brand: " + this->brand + "\n";
        str += "price: " + doubleToString(this->price, 2) + "\n";
        str += "count: " + to_string(this->count);
        return str;
    }
};

class StockList
{
private:
    class Node
    {
    private:
        HomeAppliance data;
        Node *next;
        friend class StockList;

    public:
        Node()
        {
            this->next = NULL;
        }
        Node(HomeAppliance data, Node *next)
        {
            this->data = data;
            this->next = next;
        }
    };
    Node *head;
    int _size;

public:
    class Iterator
    {
    private:
        Node *iter;
        friend class StockList;

    public:
        Iterator()
        {
            iter = NULL;
        }
        Iterator(Node *iter)
        {
            this->iter = iter;
        }
        HomeAppliance operator*()
        {
            if (iter)
                return iter->data;
            HomeAppliance data;
            return data;
        }
        Iterator operator++()
        {
            iter = iter->next;
            return *this;
        }
        bool operator==(const Iterator &other)
        {
            return iter == other.iter;
        }
        bool isNull()
        {
            return iter == NULL;
        }
    };
    StockList()
    {
        head = NULL;
        _size = 0;
    }
    int size() const
    {
        return _size;
    }
    void insert(HomeAppliance homeAppliance)
    {
        _size++;
        Iterator pre;
        Iterator now(head);
        bool flag = true;
        while (now.iter)
        {
            if (now.iter->data == homeAppliance)
            {
                now.iter->data = homeAppliance;
                flag = false;
                _size--;
                break;
            }
            else if (homeAppliance < now.iter->data)
            {
                if (pre.iter)
                {
                    pre.iter->next = new Node(homeAppliance, now.iter);
                }
                else
                {
                    head = new Node(homeAppliance, now.iter);
                }
                flag = false;
                break;
            }
            pre = now;
            ++now;
        }
        if (flag)
        {
            if (pre.iter)
            {
                pre.iter->next = new Node(homeAppliance, NULL);
            }
            else
            {
                head = new Node(homeAppliance, NULL);
            }
        }
    }
    Iterator find(string name)
    {
        Iterator now(head);
        while (now.iter)
        {
            if (now.iter->data.getName() == name)
            {
                return now;
            }
            ++now;
        }
        return now;
    }
    void erase(Iterator iter)
    {
        Iterator pre;
        Iterator now(head);
        while (now.iter)
        {
            if (now == iter)
            {
                pre.iter->next = now.iter->next;
                delete now.iter;
                break;
            }
            pre = now;
            ++now;
        }
    }
    Iterator begin()
    {
        Iterator iter(head);
        return iter;
    }
    vector<HomeAppliance> getAll()
    {
        vector<HomeAppliance> res;
        Iterator iter(head);
        while (!iter.isNull())
        {
            res.push_back(iter.iter->data);
            ++iter;
        }
        return res;
    }
};

class Warehouse
{
private:
    StockList stockList;
    friend class WarehouseSystem;

public:
    int addItem(HomeAppliance homeAppliance)
    {
        stockList.insert(homeAppliance);
        return 0;
    }
    int addItem(vector<string> command) //0: 成功；1: 非法参数。
    {
        if (command.size() < 5 || !Type::isNumber(command[3]) || !Type::isNumber(command[4]))
        {
            cout << "【错误】请输入合法的 add 命令：" << endl;
            cout << "add <name> <brand> <price> <amount>\t\t添加名为 name，品牌为 brand，价格为 price，数量为 amount 的库存。" << endl;
            return 1;
        }
        string name = command[1];
        string brand = command[2];
        double price = stod(command[3]);
        int count = stoi(command[4]);
        HomeAppliance homeAppliance(name, brand, price, count);
        addItem(homeAppliance);
        cout << "成功添加商品 " << command[1] << endl;
        return 0;
    }
    int putItem(vector<string> command) //0: 成功；1: 添加商品；2: 非法参数。
    {
        if (command.size() < 3 || !Type::isNumber(command[2]))
        {
            cout << "【错误】请输入合法的 put 命令：" << endl;
            cout << "put <name> <amount>\t\t名为 name 的商品增加 amount 个库存。" << endl;
            return 2;
        }
        StockList::Iterator it = stockList.find(command[1]);
        if (it.isNull())
        {

            cout << "【错误】商品不存在，请使用 add 命令添加商品。" << endl;
            cout << "add <name> <brand> <price> <amount>\t\t添加名为 name，品牌为 brand，价格为 price，数量为 amount 的库存。" << endl;
            return 1;
        }
        else
        {
            int count = Type::parseInt(command[2]);
            HomeAppliance homeAppliance = *it;
            int total = homeAppliance.getCount() + count;
            homeAppliance.setCount(total);
            stockList.erase(it);
            stockList.insert(homeAppliance);
            cout << "【库存更新】" << command[1] << " 的库存修改为 " << total << endl;
        }
        return 0;
    }
    int getItem(vector<string> command) //0: 成功；1: 商品不足；2: 商品不存在；3: 非法参数。
    {
        if (command.size() < 3 || !Type::isNumber(command[2]))
        {
            cout << "【错误】请输入合法的 get 命令：" << endl;
            cout << "get <name> <amount>\t\t名为 name 的商品减少 amount 个库存。" << endl;
            return 3;
        }
        StockList::Iterator it = stockList.find(command[1]);
        if (it.isNull())
        {

            cout << "【错误】商品不存在，请使用 add 命令添加商品。" << endl;
            cout << "add <name> <brand> <price> <amount>\t\t添加名为 name，品牌为 brand，价格为 price，数量为 amount 的库存。" << endl;
            return 1;
        }
        else
        {
            int count = Type::parseInt(command[2]);
            HomeAppliance homeAppliance = *it;
            int total = homeAppliance.getCount() - count;
            if (total < 0)
            {
                cout << "【错误】库存不足！" << endl;
                return 1;
            }
            homeAppliance.setCount(total);
            stockList.erase(it);
            stockList.insert(homeAppliance);
            cout << "【库存更新】" << command[1] << " 的库存修改为 " << total << endl;
        }
        return 0;
    }
    int query(vector<string> command) //0: 查询成功；1: 商品不存在；2: 非法参数。
    {
        if (command.size() < 2)
        {
            cout << "【错误】请输入合法的 query 命令：" << endl;
            cout << "query <name>\t\t调出出名为 name 的商品的所有信息。" << endl;
            cout << "query --all\t\t调出所有商品信息。" << endl;
            return 2;
        }
        if (command[1] == "--all")
        {
            vector<HomeAppliance> homeAppliances = stockList.getAll();
            for (int i = 0; i < homeAppliances.size(); i++)
            {
                cout << homeAppliances[i].toString() << endl
                     << endl;
            }
            return 0;
        }
        else
        {
            StockList::Iterator it = stockList.find(command[1]);
            if (it.isNull())
            {
                cout << "【错误】商品不存在" << endl
                     << endl;
                return 1;
            }
            else
            {
                cout << (*it).toString() << endl;
            }
        }
        return 0;
    }
};

class WarehouseSystem
{
private:
    string command;
    Warehouse warehouse;
    vector<string> commandSpilt(string command)
    {
        bool findBegin = true;
        int begin = 0, end;
        vector<string> strings;
        for (int i = 0; i < command.size(); i++)
        {
            if (findBegin && !(command[i] == ' ' || command[i] == '\t' ||
                               command[i] == '\r' || command[i] == '\n'))
            {
                begin = i;
                findBegin = false;
            }
            else if (!findBegin && (command[i] == ' ' || command[i] == '\t' ||
                                    command[i] == '\r' || command[i] == '\n'))
            {
                end = i - 1;
                findBegin = true;
                strings.push_back(command.substr(begin, end - begin + 1));
            }

            if (i == command.size() - 1 &&
                !(command[i] == ' ' || command[i] == '\t' || command[i] == '\r' || command[i] == '\n'))
            {
                end = i;
                findBegin = true;
                strings.push_back(command.substr(begin, end - begin + 1));
            }
        }
        return strings;
    }
    int doCommand(string command)
    {
        vector<string> strings = commandSpilt(command);
        if (strings.size() == 0)
            return 1;
        if (strings[0] == "--help")
            showHelp();
        else if (strings[0] == "add")
        {
            int res = warehouse.addItem(strings);
            if (res == 0)
            {
            }
        }
        else if (strings[0] == "put")
        {
            int res = warehouse.putItem(strings);
            if (res == 0)
            {
                // cout << "【库存更新】" << strings[1] << " 的库存修改为 " << strings[2] << endl;
            }
            else if (res == 1)
            {
            }
            else
            {
            }
        }
        else if (strings[0] == "get")
        {
            int res = warehouse.getItem(strings);
        }
        else if (strings[0] == "query")
        {
            int res = warehouse.query(strings);
            if (res == 1)
            {
            }
            else if (res == 2)
            {
            }
        }
        else if (strings[0] == "exit")
        {
            shutdown();
            return -1;
        }
        else
        {
            cout << "未知命令：" << strings[0] << endl;
            cout << "请使用 --help 查询命令的使用方法。" << endl;
        }
        return 0;
    }
    void showHelp()
    {
        cout << "put <name> <amount>"
             << "\t名为 <name> 的商品增加 <amount> 个库存。" << endl;
    }
    void init()
    {
        cout << "程序启动..." << endl;
        cout << "正在读取数据..." << endl;

        streambuf *backup;
        ifstream fin;
        fin.open("data.txt");
        backup = cin.rdbuf();   // back up cin's streambuf
        cin.rdbuf(fin.rdbuf()); // assign file's streambuf to cin
        // ... cin will read from file
        int countOfItem;
        cin >> countOfItem;
        for (int i = 1; i <= countOfItem; i++)
        {
            string name;
            string brand;
            double price;
            int count;
            cin >> name >> brand >> price >> count;
            HomeAppliance homeAppliance(name, brand, price, count);
            warehouse.addItem(homeAppliance);
        }
        cin.rdbuf(backup); // restore cin's original streambuf
        cout << "数据读取完成！" << endl;
        cout << "开始营业。" << endl;
        cout << "输入 --help 查询命令的使用方法。" << endl;
    }
    void shutdown()
    {
        cout << endl
             << "正在保存数据..." << endl;
        // cout << "正在读取数据..." << endl;

        ofstream fout("data.txt"); //输出文件
        streambuf *coutbackup;
        coutbackup = cout.rdbuf(fout.rdbuf()); //用 rdbuf() 重新定向，返回旧缓冲区指针

        vector<HomeAppliance> homeAppliances = warehouse.stockList.getAll();
        cout << homeAppliances.size() << endl;
        for (int i = 0; i < homeAppliances.size(); i++)
        {
            cout << homeAppliances[i].getName() << " " << homeAppliances[i].getBrand()
                 << " " << homeAppliances[i].getPrice() << " " << homeAppliances[i].getCount() << endl;
        }

        cout.rdbuf(coutbackup); //取消，恢复屏幕输出

        cout << "数据保存完成！" << endl;
        cout << "结束营业。" << endl;
        // cout << "输入 --help 查询命令的使用方法。" << endl;
    }

public:
    void run()
    {
        init();

        while (true)
        {
            // cout << "\033[1;31mbold red text\033[0m\n";
            cout << "\033[1;34mroot@system ~ \033[0m";
            cin.clear();
            getline(cin, command);
            // cout << command << endl;
            int res = doCommand(command);
            if (res == -1)
                break;
        }
    }
};

int main()
{
    WarehouseSystem warehouseSystem;
    warehouseSystem.run();
    return 0;
}