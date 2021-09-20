#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

class Class;
class Teacher;
class Student;

class Teacher
{
private:
    string name;
    int age;
    Class *cls;
    bool inClass;

public:
    Teacher(string name, int age)
    {
        this->name = name;
        this->age = age;
    }
    void setClass(Class *cls)
    {
        this->cls = cls;
    }
    void setInClass(bool inClass)
    {
        this->inClass = inClass;
    }
    bool getInClass()
    {
        return this->inClass;
    }
    void talk(string message)
    {
        if (this->inClass)
        {
            if (message.compare("下课！"))
            {
                printf("%s老师：下课！\n", this->name.data());
                this->inClass = 0;
                this->cls->classOver();
            }
        }
    }
};

class Student
{
private:
    string name;
    int studentID;
    int weight;

public:
    Student(string name, int studentID, int weight)
    {
        this->name = name;
        this->studentID = studentID;
        this->weight = weight;
    }
    void eat()
    {
        printf("%s同学 吃饭。\n", this->name.data());
        this->weight++;
        printf("%s同学 的体重增加到了%dkg。\n", this->name.data(), this->weight);
    }
};

class Class
{
private:
    int courseID;
    struct Teacher *teacher;
    int studentNumber;
    struct Student *student;

public:
    Class(int courseID, Teacher *teacher, Student *student)
    {
        this->courseID = courseID;

        this->teacher = teacher;
        teacher->setClass(this);
        teacher->setInClass(1);

        this->student = student;
    }
    void classOver()
    {
        this->student->eat();
    }
};

int main()
{
    Student student("小明", 233, 60);
    Teacher teacher("李华", 30);
    Class cls(1, &student, &teacher);
    return 0;
}