#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int count;
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

  do{
    while(fac[i] <= fac[pivot] && i<high) {
      i++;
    }
    while(fac[j] > fac[pivot]) {
      j--;
    }
    if(i < j) {
      swap(&fac[i], &fac[j]);
    }
  } while(i < j);

  swap(&fac[pivot], &fac[j]);
  return j;
}

int randomPartition(int arr[], int low, int high) {
    srand(time(NULL));
    int randomIndex = low + rand() % (high - low + 1);
    return partition(arr, low, high);
}

void quickSort(int fac[], int low, int high) {
  int partitionIndex;
  if(low < high) {
    partitionIndex = randomPartition(fac, low, high);
    quickSort(fac, low, partitionIndex - 1);
    quickSort(fac, partitionIndex + 1, high);
  }
}

int main() {
  int n, arr[]={32,52,14,35,12,55,32,115,8,56};
  n = sizeof(arr)/sizeof(arr[0]);
  int matrix[n][n];
  for(int i=0; i<n; i++) {
    for(int j=0; j<n-i-1; j++) {
        matrix[i][j] = 0;
    }
  }
  quickSort(arr, 0, n-1);
  printf("\nSorting using Quick Sort: ");
  for(int i = 0; i < n; i++) {
    printf("%d\t",arr[i]);
  } 
  return 0;
}
