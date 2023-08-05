#include <stdio.h>

int SIZE;
int front = -1;
int rare = -1;
int b;

void enqueue(int Queue[], int data){
  if(rare == SIZE - 1){
    printf("Queue Overflow\n");
  } 
  else{
    if(front == -1){
        front = 0;
    }
    rare++;
    printf("%d  ",data);
    Queue[rare] = 1;
  }
}

void dequeue(int Queue[], int pos){
    int count = 0;
    while(count < pos){
        front = front%SIZE;
        if(Queue[front] == 1){
            count++;
            front++;
        }
        else{
            front++;
        }
    }

    printf("Killed person at pos: %d\n",front);
    Queue[front-1] = 0;

    while (Queue[front] != 1) {
        front++;
        front = front%SIZE;
    }
}

int main(){
    int a;
    printf("Enter the number of people: "); 
    scanf("%d", &SIZE);
    printf("Enter your position: ");
    scanf("%d", &a);

    int Queue[SIZE];
    printf("Circular List of person: ");
    for(int i=1; i<SIZE+1; i++){
        enqueue(Queue, i);
    }

    printf("\n");
    for(int i=0; i<SIZE-1; i++){
        dequeue(Queue,a);
    }

    printf("\nSurvived Person is at position: %d",front+1);
    return 0;
}

