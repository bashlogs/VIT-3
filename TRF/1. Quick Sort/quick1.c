//WAP to implement Bucket Sort and Quick sort on 1D array of Faculty
//structure (contains faculty_name, faculty_ID, subject_codes,
//class_names), with key as faculty_ID. And count the number of swap
//performed

#include <stdio.h>
#include <string.h>
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

void quickSort(int fac[], int low, int high) {
  int partitionIndex;
  if(low < high) {
    partitionIndex = partition(fac, low, high);
    quickSort(fac, low, partitionIndex - 1);
    quickSort(fac, partitionIndex + 1, high);
  }
}

int main() {
  int n, arr[]={32,52,14,35,12,55,32,115,8,56};
  n = sizeof(arr)/sizeof(arr[0]);
  quickSort(arr, 0, n-1);
  printf("\nSorting using Quick Sort: ");
  for(int i = 0; i < n; i++) {
    printf("%d\t",arr[i]);
  } 
  printf("\nSwap count : %d\n", count);
  return 0;
}
