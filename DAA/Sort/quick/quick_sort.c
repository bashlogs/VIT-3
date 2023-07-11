#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count;
int **matrix;

void swap(int *a, int *b) {
  int t;
  t = *a;
  *a = *b;
  *b = t;
  count++;
}
int partition(int fac[], int low, int high) {
  int pivot = low;
  int i = low + 1;
  int j = high;
  int tfac;

  while(i < j){
    while(fac[i] < fac[pivot]) {
      i++;
    }
    while(fac[j] > fac[pivot]) {
      j--;
    }
    if(i < j) {
      swap(&fac[i], &fac[j]);
      matrix[i][j] += 1;
      printf("Swap: (%d, %d)\n", fac[i], fac[j]);
    }
  }

  swap(&fac[pivot], &fac[j]);
  matrix[i][j] += 1;
  printf("Swap: (%d, %d)\n", fac[i], fac[j]);
  return j;
}

void quickSort(int fac[], int low, int high) {
  int partitionIndex;
  if(low < high) {
    partitionIndex = partition(fac, low, high);
    quickSort(fac, low, partitionIndex - 1);
    quickSort(fac, partitionIndex + 1, high); 
  }
}

void printarray(int arr[], int size){
  for(int i=0; i<size; i++){
    printf("%d\t",arr[i]);
  }
  printf("\n");
}

int main() {
  int n, arr[]={32,52,14,35,12,55,32,115,8,56};
  n = sizeof(arr)/sizeof(arr[0]);

  matrix = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) {
      matrix[i] = (int *)malloc(n * sizeof(int));
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        matrix[i][j] = 0;
    }
  }

  quickSort(arr, 0, n-1);
  printf("Unsorted array: ");
  printarray(arr, n);
  printf("Sorted array: ");
  printarray(arr, n);
  printf("\n");

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        printf("%d\t", matrix[i][j]);
    }
    printf("\n");
  }

  return 0;
}
