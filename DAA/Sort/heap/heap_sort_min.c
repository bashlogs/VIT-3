#include <stdio.h>
#include <stdlib.h>

void minheapify(int a[], int node, int size);

void printarray(int a[], int size){
    for(int i=0; i<size; i++){
        printf("%d\t",a[i]);
    }
    printf("\n");
}

void minheapify(int a[], int node, int size){
    int max = node;
    int left = 2*max;
    int right = 2*max+1;
    int t;

    if(left < size && a[left] < a[max]){
        max = left;
    }
    if(right < size && a[right] < a[max]){
        max = right;
    }
    if(node != max){
        t = a[node];
        a[node] = a[max];
        a[max] = t;
        minheapify(a,max,size);
    }
}

void minheap(int a[], int min, int size){
    for(int i = size/2-1; i >= min; i--){
        minheapify(a, i, size);
    }
}

void heapsort(int a[],int size){
    int i, t;
    for(int i=size-1; i > size-4; i--){
        t = a[0];
        a[0] = a[i];
        a[i] = t;
        minheapify(a,0,i);
    }
}

int main(){
    int a[] = {3,2,1,5,6,4};
    int size = sizeof(a)/sizeof(a[0]);
    printf("%d\n",size);
    minheap(a, 0, size);
    heapsort(a,size);
    printarray(a,size);
    return 0;
}