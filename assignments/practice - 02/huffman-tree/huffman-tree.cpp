#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <bitset>
using namespace std;

class BitSet
{
private:
    char *data;
    int size;
    int capacity;

public:
    BitSet();
    BitSet(const vector<bool> &bitStream);
    BitSet operator=(const vector<bool> &bitStream);
    void write(const string &path);
    vector<bool> read(const string &path);
};

class HuffmanTree
{
private:
    class HuffmanTreeNode
    {
    private:
        friend class HuffmanTree;
        char data;
        double frequency;
        bool isLeaf;
        HuffmanTreeNode *lchild, *rchild;

    public:
        HuffmanTreeNode(char data, double frequency);
        HuffmanTreeNode(double frequency, HuffmanTreeNode *lchild, HuffmanTreeNode *rchild);
        bool operator<(const HuffmanTreeNode &huffmanTreeNode);
    };
    vector<bool> code[128];
    int countOfChars[128];
    double frequencyOfChars[128];
    HuffmanTreeNode *root;
    void getCode(HuffmanTreeNode *rt, vector<bool> &currentCode);

public:
    HuffmanTree(const string &text);
    void debug();
    vector<bool> encode(const string &str);
    string decode(const vector<bool> &bitStream);
};

int main()
{
    fstream fin;
    fin.open("article.txt");
    string str;
    char ch;
    while (fin.get(ch))
    {
        str.append(1, ch);
    }

    HuffmanTree huffmanTree(str);
    vector<bool> encodedCode = huffmanTree.encode(str);

    fstream fout("binary.txt", ios::out);
    for (bool bit : encodedCode)
    {
        fout << bit;
    }
    fout.close();

    BitSet bitSet(encodedCode);
    bitSet.write("binary.dat");

    fout.open("decode-result.txt", ios::out);
    fout << huffmanTree.decode(bitSet.read("binary.dat"));
    return 0;
}

HuffmanTree::HuffmanTreeNode::HuffmanTreeNode(char data, double frequency)
{
    this->data = data;
    this->frequency = frequency;
    isLeaf = true;
    lchild = rchild = nullptr;
}
HuffmanTree::HuffmanTreeNode::HuffmanTreeNode(double frequency, HuffmanTreeNode *lchild, HuffmanTreeNode *rchild)
{
    this->data = 0;
    this->frequency = frequency;
    isLeaf = false;
    this->lchild = lchild;
    this->rchild = rchild;
}
bool HuffmanTree::HuffmanTreeNode::operator<(const HuffmanTreeNode &huffmanTreeNode)
{
    return this->frequency > huffmanTreeNode.frequency;
}
HuffmanTree::HuffmanTree(const string &text0)
{
    string text = text0 + '\0';
    if (text.length() == 0)
        return;
    for (int i = 0; i < 128; i++)
    {
        countOfChars[i] = 0;
        frequencyOfChars[i] = 0;
    }
    for (const char &ch : text)
    {
        countOfChars[ch]++;
    }
    auto huffmanTreeNodePointerGreater = [](const HuffmanTreeNode *a, const HuffmanTreeNode *b)
    {
        if (a == nullptr || b == nullptr)
            return false;
        return a->frequency > b->frequency;
    };
    using HuffmanTreeNodePriorityQueue =
        priority_queue<HuffmanTreeNode *,
                       vector<HuffmanTreeNode *>,
                       bool (*)(const HuffmanTreeNode *a,
                                const HuffmanTreeNode *b)>;
    HuffmanTreeNodePriorityQueue q(huffmanTreeNodePointerGreater);
    for (int i = 0; i < 128; i++)
    {
        frequencyOfChars[i] = double(countOfChars[i]) / text.length();
        q.push(new HuffmanTreeNode(i, frequencyOfChars[i]));
    }
    while (q.size() > 1)
    {
        HuffmanTreeNode *lchild = q.top();
        q.pop();
        HuffmanTreeNode *rchild = q.top();
        q.pop();
        if (q.size() % 2)
            swap(lchild, rchild);
        HuffmanTreeNode *huffmanTreeNode =
            new HuffmanTreeNode(lchild->frequency + rchild->frequency, lchild, rchild);
        q.push(huffmanTreeNode);
    }
    root = q.top();
    vector<bool> currentCode;
    getCode(root, currentCode);
    debug();
}

void HuffmanTree::debug()
{
    fstream fout("huffman-encode-list.txt", ios::out);

    cout.setf(ios::fixed);
    for (int i = 0; i < 128; i++)
    {
        fout << "ascii code: " << setw(3) << setfill(' ') << i << ", "
             << "frequency: " << fixed << setprecision(7) << frequencyOfChars[i] << ", "
             << "huffman code: ";
        //  << endl;
        for (int j = 0; j < code[i].size(); j++)
        {
            fout << int(code[i][j]);
        }
        fout << endl;
    }

    cout.unsetf(ios::fixed);
}

void HuffmanTree::getCode(HuffmanTreeNode *rt, vector<bool> &currentCode)
{
    if (rt->isLeaf)
    {
        code[rt->data] = currentCode;
        return;
    }
    currentCode.push_back(false);
    getCode(rt->lchild, currentCode);
    currentCode.pop_back();
    currentCode.push_back(true);
    getCode(rt->rchild, currentCode);
    currentCode.pop_back();
}

vector<bool> HuffmanTree::encode(const string &str0)
{
    string str = str0 + '\0';
    vector<bool> res;
    for (const char ch : str)
    {
        for (bool bit : code[ch])
        {
            res.push_back(bit);
        }
    }
    return res;
}

string HuffmanTree::decode(const vector<bool> &bitStream)
{
    string res;
    int pos = 0;
    while (pos != bitStream.size())
    {
        HuffmanTreeNode *now = root;
        while (!now->isLeaf)
        {
            if (pos >= bitStream.size() || now == nullptr)
                return res;
            if (bitStream[pos])
                now = now->rchild;
            else
                now = now->lchild;
            pos++;
        }
        if (now->data == 0)
            break;
        res.append(1, now->data);
    }
    return res;
}

BitSet::BitSet()
{
    data = nullptr;
    size = capacity = 0;
}
BitSet::BitSet(const vector<bool> &bitStream)
{
    data = nullptr;
    size = capacity = 0;
    (*this) = bitStream;
}
BitSet BitSet::operator=(const vector<bool> &bitStream)
{
    if (data != nullptr)
        delete[] data;
    size = bitStream.size();
    if (size % 8 == 0)
        capacity = size / 8;
    else
        capacity = size / 8 + 1;
    data = new char[capacity];
    for (int i = 0, pos = 0; i < bitStream.size(); i++)
    {
        int currentBitPosInPos = i % 8;
        if (currentBitPosInPos == 0)
            data[pos] = 0;
        if (bitStream[i])
            data[pos] |= (1 << (7 - currentBitPosInPos));
        if (currentBitPosInPos == 7)
            pos++;
    }
    return *this;
}
void BitSet::write(const string &path)
{
    fstream fout(path.c_str(), ios::out | ios::binary);
    fout.write((char *)&capacity, sizeof(capacity));
    // for (int i = 0; i < capacity; i++)
    // {
    //     for (int j = 7; j >= 0; j--)
    //     {
    //         if (data[i] & (1 << j))
    //             fout << 1;
    //         else
    //             fout << 0;
    //     }
    // }
    fout.write((char *)data, capacity * sizeof(char));
    fout.close();
}

vector<bool> BitSet::read(const string &path)
{
    if (data != nullptr)
        delete[] data;

    vector<bool> res;

    fstream fin(path.c_str(), ios::in | ios::binary);
    fin.read((char *)&capacity, sizeof(capacity));
    size = capacity;
    data = new char[capacity];
    for (int i = 0; i < capacity; i++)
    {
        fin.read((char *)&data[i], sizeof(data[i]));
        for (int j = 7; j >= 0; j--)
        {
            if (data[i] & (1 << j))
                res.push_back(true);
            else
                res.push_back(false);
        }
    }

    return res;
}