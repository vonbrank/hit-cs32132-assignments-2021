#include <stdio.h>

typedef struct a
{
    char name[N];
    char brand[N];
    float price;
    int storage;
    struct a *next;
} appliance;

void creat(appliance *head)
{
    if (head != NULL)
    {
        do
        {
            int i = 0;
            scanf("%d", &i);
            if (i == 1)
            {
                appliance *pr, *p = malloc(sizeof(appliance));
                gets(p->name);
                gets(p->brand);
                scanf("%f %d", &p->price, p->storage);
                if (head->next == NULL)
                {
                    head->next = p;
                }
                else
                {
                    pr->next = p;
                    pr = p;
                    p->next = NULL;
                } /* code */
            }
        } while (i == 1);
    }
    return;
}

void BubbleSort(appliance *head)
{
    appliance *p = head->next, *q = head->next;
    while (q->next != NULL)
    {
        while (p->next != NULL)
        {
            if (p->price > p->next->price)
            {
                float temp = p->price;
                p->price = p->next->price;
                p->next - price = temp;
            }
            p = p->next;
        }
        q = q->next;
    }
    return;
}

int main()
{
    appliance *head = malloc(sizeof(appliance));
    head->next = NULL;
    creat(head);
    BubbleSort(head);
    int choice;
    do
    {
        scanf("%d", &choice);
        if (choice == 1)
        {
            Insert(head);
        }
        else if (choice == 2)
        {
            Delete(head);
        }
        else if (choice == 3)
        {
            Index(head);
        }
        else if (choice == 4)
        {
            Output(head);
        }
    } while (choice > 0);
}