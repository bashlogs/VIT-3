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
  srand(time(NULL)); 
  int pivot = low + rand() % (high - low + 1); 
  int i = low + 1;
  int j = high;

  while (i < j) {
    while (fac[i] < fac[pivot]) {
      matrix[i][pivot] += 1;
      i++;
    }
    while (fac[j] > fac[pivot]) {
      matrix[j][pivot] += 1;
      j--;
    }
    if (i < j) {
      swap(&fac[i], &fac[j]);
      printf("Swap: (%d, %d)\n", fac[i], fac[j]);
    }
  }

  swap(&fac[pivot], &fac[j]);
  printf("Swap: (%d, %d)\n", fac[i], fac[j]);
  return j;
}

void quickSort(int fac[], int low, int high) {
  int partitionIndex;
  if (low < high) {
    partitionIndex = partition(fac, low, high);
    quickSort(fac, low, partitionIndex - 1);
    quickSort(fac, partitionIndex + 1, high);
  }
}

void printarray(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d\t", arr[i]);
  }
  printf("\n");
}

int main() {
  int n, arr[] = {73, 39, 21, 53, 89, 93, 12, 43};
  n = sizeof(arr) / sizeof(arr[0]);
  
  printf("Unsorted array: ");
  printarray(arr, n);
  
  quickSort(arr, 0, n - 1);
  
  printf("Sorted array: ");
  printarray(arr, n);

  return 0;
}
