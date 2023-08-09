#include <stdio.h>
#include <stdlib.h>
 
struct node
{
    int num;
    struct node *next;
};

struct queue
{
    struct node* head;
    struct node* front;
    struct node* rear;
};


int dequeue(struct queue* q)
{
    struct node* t;
    int x;
    t = q->front;
    x = t->num;
    q->front = q->front->next;
    q->rear->next = q->front;
    free(t);
    return x;
}

 
void enqueue(struct queue* q, int x)
{
    struct node* p = (struct node*)malloc(sizeof(struct node));
    p->num = x;
    if (q->head->next == NULL)
    {
        q->front = q->rear = p;
        q->head->next = p;
        p->next = p;
    }
    else
    {
        q->rear->next = p;
        p->next = q->front;
        q->rear = q->rear->next;
    }
}

 
void display(struct queue* q)
{
    struct node* p = q->front;
    do
    {
        printf("%d  ", p->num);
        p = p->next;
    } while (p != q->rear->next);
}

void move_next(struct queue* q)
{
    q->front = q->front->next;
    q->rear = q->rear->next;
}


int main()
{
    struct queue e;
    e.head = (struct node*)malloc(sizeof(struct node));
    e.head->next = NULL;
    e.front = e.rear = e.head;
    
    int m, n, i, d,a=2;
    printf("Enter the number of peoples: ");
    scanf("%d", &n);
    
    printf("Every alternate person is killed\n");
    // scanf("%d", &a);

    for (i = 1; i <= n; i++)
        enqueue(&e, i);
    
    printf("List: ");
    display(&e);
    
    printf("\nEliminated in order: ");
    while (n > 1)
    {
        for (i = 1; i < a; i++)
            move_next(&e);
        d = dequeue(&e);
        printf("%d  ", d);
        n--;
    }
    d = dequeue(&e);
    printf("\n\nWinning player: %d\n", d);
    free(e.head);

    return 0;
}