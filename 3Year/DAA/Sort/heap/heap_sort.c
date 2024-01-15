#include <stdio.h>
#include <stdlib.h>

void maxheapify(int a[], int node, int size);

void printarray(int a[], int size){
    for(int i=0; i<size; i++){
        printf("%d\t",a[i]);
    }
    printf("\n");
}

void maxheapify(int a[], int node, int size){
    int max = node;
    int left = 2*max;
    int right = 2*max+1;
    int t;

    if(left < size && a[left] > a[max]){
        max = left;
    }
    if(right < size && a[right] > a[max]){
        max = right;
    }
    if(node != max){
        t = a[node];
        a[node] = a[max];
        a[max] = t;
        maxheapify(a,max,size);
    }
}

void maxheap(int a[], int min, int size){
    for(int i = size/2-1; i >= min; i--){
        maxheapify(a, i, size);
    }
}

void heapsort(int a[],int size){
    int i, t;
    for(int i=size-1; i > 0; i--){
        t = a[0];
        a[0] = a[i];
        a[i] = t;
        maxheapify(a,0,i);
    }
}

int main(){
    int a[] = {6, 14, 3, 26, 8, 18, 21, 9, 5};
    int size = sizeof(a)/sizeof(a[0]);
    printf("%d\n",size);
    maxheap(a, 0, size);
    heapsort(a,size);
    printarray(a,size);
    return 0;
}