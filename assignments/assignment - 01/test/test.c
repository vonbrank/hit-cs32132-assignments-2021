#include <stdio.h>
struct a
{
    int num;
    struct a *next;
};
struct a *build(struct a *head)
{
    return head;
}
int main()
{

    struct a *head = NULL;
    head = build(head);
    return 0;
}
