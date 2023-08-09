#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

  while (i < j) {
    while (fac[i] < fac[pivot] && i <= high) {
      matrix[i][pivot] += 1;
      matrix[pivot][i] += 1;
      i++;
    }
    while (fac[pivot] < fac[j] && j >= low + 1) {
      matrix[pivot][j] += 1;
      matrix[j][pivot] += 1;
      j--;
    }

    if (i < j) {
      // matrix[i][j] += 1;
      swap(&fac[i], &fac[j]);
      printf("Swap: (%d, %d)\n", fac[i], fac[j]);
    }
  }

  // matrix[pivot][j] += 1;
  swap(&fac[pivot], &fac[j]);
  printf("Swap: (%d, %d)\n", fac[pivot], fac[j]);
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
  int n, arr[]={4,3,2,1};
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

  printf("Unsorted array: ");
  printarray(arr, n);

  quickSort(arr, 0, n-1);

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
