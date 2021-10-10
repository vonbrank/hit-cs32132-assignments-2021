#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include "IO.h"
#include "Random.h"

using namespace std;

class DayTime
{
private:
    int hour;
    int minute;
    int second;

public:
    DayTime();
    DayTime(int hour, int minute, int second);
    DayTime operator++();
    DayTime operator+(const DayTime &dayTime);
    string toString();
};

class Student
{
private:
    string name;
    string studentID;
    int gender;
    int startWaitingTime;

public:
    Student();
    Student(string name, string studentID, int gender);
    string getName() const;
    void setStartWaitingTime(int startWaitingTime);
    int getStartWaitingTime();
};

class Restaurant;
class SellWindow
{
private:
    string name;
    queue<Student> waitingQueue;
    Restaurant *restaurant;
    int timeLeft;
    int timeOfService;
    int lastTime;

public:
    SellWindow(string name, Restaurant *restaurant);
    int countOfWaitings();
    void offerServices();
    void getStudent(const Student &student);
    int lengthOfWaitings();
};

class Restaurant
{
private:
    string name;
    int currentTime;
    int startTime;
    int endTime;
    int totalWaitingTime;
    int countOfCompletedWaiting;
    queue<pair<int, Student>> students;
    vector<SellWindow> sellWindows;
    void update();
    void studentAllocate();
    void windowBalanceLoader(const Student &student);
    void sellWindowsOfferService();

public:
    Restaurant(string name, int startTime, int endTime, vector<pair<int, Student>> &students, vector<string> &nameOfSellWindows);
    void run();
    int getCurrentTime();
    string timeNow();
    void addTotalWaitingTime(int time);
    void addCountOfCompletedWaiting(int count);
    double getAverageWaitingTime();
};

DayTime::DayTime()
{
    hour = minute = second = 0;
}

DayTime::DayTime(int hour, int minute, int second)
{
    this->second = second;
    this->minute = minute;
    this->hour = hour;

    this->minute += this->second / 60;
    this->second %= 60;

    this->hour += this->minute / 60;
    this->minute %= 60;

    this->hour %= 24;
}

DayTime DayTime::operator++()
{
    second++;
    if (second == 60)
    {
        second = 0;
        minute++;
    }
    if (minute == 60)
    {
        minute = 0;
        hour++;
    }
    if (hour == 24)
        hour = 0;
    return *this;
}

DayTime DayTime::operator+(const DayTime &dayTime)
{
    int second = 0, minute = 0, hour = 0;
    second += this->second + dayTime.second;
    if (second >= 60)
    {
        second -= 60;
        this->minute++;
    }
    minute += this->minute + dayTime.minute;
    if (minute >= 60)
    {
        minute -= 60;
        hour++;
    }
    hour += this->hour + dayTime.hour;
    return DayTime(hour, minute, second);
}

string DayTime::toString()
{
    auto toTwoString = [&](int x)
    {
        string str = to_string(x);
        if (str.length() == 1)
            str = "0" + str;
        return str;
    };

    string str = toTwoString(hour) + ":" + toTwoString(minute) + ":" + toTwoString(second);
    return str;
    // return string(itos(hour) + ":" + itos(minute) + ":" + itos(second));
}

Student::Student()
    : name(""), studentID(""), gender(0) {}

Student::Student(string name, string studentID, int gender)
    : name(name), studentID(studentID), gender(gender) {}

string Student::getName() const
{
    return name;
}

void Student::setStartWaitingTime(int startWaitingTime)
{
    this->startWaitingTime = startWaitingTime;
}

int Student::getStartWaitingTime()
{
    return startWaitingTime;
}

SellWindow::SellWindow(string name, Restaurant *restaurant)
    : name(name), restaurant(restaurant), timeLeft(0), timeOfService(20) {}

int SellWindow::countOfWaitings()
{
    return waitingQueue.size();
}

void SellWindow::offerServices()
{
    if (timeLeft != 0)
    {
        timeLeft--;
        if (timeLeft == 0)
        {
            Student student = waitingQueue.front();
            waitingQueue.pop();
            restaurant->addTotalWaitingTime(restaurant->getCurrentTime() - student.getStartWaitingTime());
            restaurant->addCountOfCompletedWaiting(1);
            cout << "[" << restaurant->timeNow() << "] " << student.getName() << " 同学在 " << name << " 窗口打完饭，"
                 << "耗时 " << restaurant->getCurrentTime() - student.getStartWaitingTime() << "秒，"
                 << name << " 窗口队伍长度： " << waitingQueue.size() << " 。" << endl;
        }
    }
    else
    {
        if (!waitingQueue.empty())
        {
            timeLeft = Random::randInt(10, 30);
            lastTime = restaurant->getCurrentTime();
        }
    }
}

void SellWindow::getStudent(const Student &student)
{

    waitingQueue.push(student);
    cout << "[" << restaurant->timeNow() << "] " << student.getName() << " 同学在 " << name << " 窗口排队打饭。" << endl;
}

int SellWindow::lengthOfWaitings()
{
    return waitingQueue.size();
}

void Restaurant::update()
{
    studentAllocate();
    sellWindowsOfferService();
    currentTime++;
}

void Restaurant::studentAllocate()
{
    while (!students.empty() && students.front().first <= currentTime)
    {
        Student student = students.front().second;
        students.pop();
        student.setStartWaitingTime(getCurrentTime());
        windowBalanceLoader(student);
    }
}

void Restaurant::windowBalanceLoader(const Student &student)
{
    int pos = 0, minLength = 0x7fffffff;
    for (int i = 0; i < sellWindows.size(); i++)
    {
        if (minLength > sellWindows[i].lengthOfWaitings())
        {
            minLength = sellWindows[i].lengthOfWaitings();
            pos = i;
        }
    }
    sellWindows[pos].getStudent(student);
}

void Restaurant::sellWindowsOfferService()
{
    for (int i = 0; i < sellWindows.size(); i++)
    {
        sellWindows[i].offerServices();
    }
}

string Restaurant::timeNow()
{
    return (DayTime(11, 0, 0) + DayTime(0, 0, currentTime)).toString();
}

Restaurant::Restaurant(string name, int startTime, int endTime, vector<pair<int, Student>> &students, vector<string> &nameOfSellWindows)
    : name(name), startTime(startTime), endTime(endTime), currentTime(0)
{
    for (int i = 0; i < nameOfSellWindows.size(); i++)
    {
        SellWindow sellWindow(nameOfSellWindows[i], this);
        sellWindows.push_back(sellWindow);
    }

    for (pair<int, Student> &p : students)
    {
        this->students.push(p);
    }
}

void Restaurant::run()
{
    totalWaitingTime = 0;
    countOfCompletedWaiting = 0;
    while (currentTime <= endTime)
    {
        // cout << "total waiting: " << &totalWaitingTime << endl;
        update();
    }
}

int Restaurant::getCurrentTime()
{
    return currentTime;
}

void Restaurant::addTotalWaitingTime(int time)
{
    totalWaitingTime += time;
    // cout << "total waiting: " << &totalWaitingTime << endl;
}

void Restaurant::addCountOfCompletedWaiting(int count)
{
    countOfCompletedWaiting += count;
    // cout << "count of completed waiting: " << countOfCompletedWaiting << endl;
}

double Restaurant::getAverageWaitingTime()
{
    return double(totalWaitingTime) / countOfCompletedWaiting;
}

int main()
{
    int countOfWindows;
    int countOfStudents;
    IO::inputRedirectToFile("data.txt");
    IO::outputRedirectToFile("result.txt");

    cin >> countOfWindows;
    vector<string> nameOfSellWindows;
    for (int i = 0; i < countOfWindows; i++)
    {
        string nameOfSellWindow;
        cin >> nameOfSellWindow;
        nameOfSellWindows.push_back(nameOfSellWindow);
    }

    cin >> countOfStudents;
    vector<pair<int, Student>> students;
    for (int i = 1; i <= countOfStudents; i++)
    {
        pair<int, string> p;
        cin >> p.first >> p.second;
        Student student(p.second, p.second, 0);
        students.push_back(pair<int, Student>(p.first, student));
    }

    Restaurant restaurant("TianXiang", 0, 7200, students, nameOfSellWindows);
    restaurant.run();

    IO::inputRedirectRecovery();
    IO::outputRedirectRecovery();

    cout << "学生平均等待时间：" << restaurant.getAverageWaitingTime() << "秒" << endl;
    cout << "详细排队信息已输出至 result.txt " << endl;

    return 0;
}