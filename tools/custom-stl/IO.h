#ifndef IO_H
#define IO_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class IO
{

private:
    static streambuf *oldcin;
    static streambuf *oldcout;

    static ifstream *pfin;
    static ofstream *pfout;

public:
    static void inputRedirectToFile(const std::string &path)
    { //打开 in.txt 文件，等待读取
        static ifstream fin(path);
        pfin = &fin;

        //用 rdbuf() 重新定向，返回旧输入流缓冲区指针
        oldcin = cin.rdbuf(fin.rdbuf());
    }
    static void inputRedirectRecovery()
    {
        cin.rdbuf(oldcin); // 恢复键盘输入
        (*pfin).close();
    }
    static void outputRedirectToFile(const std::string &path)
    {
        static ofstream fout(path);
        pfout = &fout;
        //打开 out.txt 文件，等待写入

        //用 rdbuf() 重新定向，返回旧输出流缓冲区指针
        oldcout = cout.rdbuf(fout.rdbuf());
    }
    static void outputRedirectRecovery()
    {
        cout.rdbuf(oldcout); //恢复屏幕输出
        (*pfout).close();
    }
};

streambuf *IO::oldcin;
streambuf *IO::oldcout;
ifstream *IO::pfin;
ofstream *IO::pfout;
#endif