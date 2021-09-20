#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Class;
struct Teacher;
struct Student;

struct Class
{
    int courseID;
    struct Teacher *teacher;
    struct Student *student;
};

struct Teacher
{
    char *name;
    int age;
    struct Class *class;
    int inClass;
};

struct Student
{
    char *name;
    int studentID;
    int weight;
};

void StudentEat(struct Student *self);

void ClassConstructor(struct Class *self, int courseID, struct Teacher *teacher, struct Student *student)
{
    self->courseID = courseID;

    self->teacher = teacher;
    teacher->class = self;
    teacher->inClass = 1;

    self->student = student;
}

void ClassClassOver(struct Class *self)
{
    StudentEat(self->student);
}

void TeacherConstructor(struct Teacher *self, char *name, int age)
{
    self->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(self->name, name);

    self->age = age;

    self->class = NULL;
    self->inClass = 0;
}

void TeacherTalk(struct Teacher *self, char *message)
{
    if (self->inClass)
    {
        if (strcmp(message, "下课！") == 0)
        {
            printf("%s老师：下课！\n", self->name);
            self->inClass = 0;
            ClassClassOver(self->class);
        }
    }
}

void StudentConstructor(struct Student *self, char *name, int studentID, int weight)
{

    self->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(self->name, name);

    self->studentID = studentID;
    self->weight = weight;
}

void StudentEat(struct Student *self)
{
    printf("%s同学 吃饭。\n", self->name);
    self->weight++;
    printf("%s同学 的体重增加到了%dkg。\n", self->name, self->weight);
}

int main()
{
    struct Student student;
    StudentConstructor(&student, "小明", 233, 60);

    struct Teacher teacher;
    TeacherConstructor(&teacher, "李华", 30);

    struct Class class;
    ClassConstructor(&class, 1, &teacher, &student);

    TeacherTalk(&teacher, "下课！");

    return 0;
}