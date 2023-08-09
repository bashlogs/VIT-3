#include <stdio.h>
#include <stdlib.h>

void quick_sort(int a[], int, int);
int partition(int a[], int, int);
float **matrix;

int main() {
  int n, c;
  printf("Enter the number of iterations: "); 
  scanf("%d", &c);
  printf("Enter no. of element: ");
  scanf("%d", &n);

  matrix = (float **)malloc(n * sizeof(float *));
  for (int i = 0; i < n; i++) {
    matrix[i] = (float *)malloc(n * sizeof(float));
    for (int j = 0; j < n; j++) {
      matrix[i][j] = 0;
    }
  }
  int arr[n];
  for(int i=0; i<c; i++){
    for(int j=0; j<=n; j++){
        arr[j] = j;
    }
    quick_sort(arr, 0, n - 1);
  }

  printf("\nSorted Array: ");
  for (int i = 0; i < n; i++) {
    printf("%d\t", arr[i]);
  }

  printf("\n\nThe number of comparisons made are as follows: \n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%.2f ", matrix[i][j]/c);
    }
    printf("\n");
  }
  return 0;
  
}

void quick_sort(int a[], int i, int j) {
  int low;
  if (i < j) {
    low = partition(a, i, j);
    quick_sort(a, i, low - 1);
    quick_sort(a, low + 1, j);
  }
}

int partition(int a[], int i, int j) {
  int right = j, left = i, flag = 0;
  int low = (rand() % (j - i + 1)) + i; 
  while (flag != 1) {
    while ((a[low] <= a[right]) && (low != right)) {
      matrix[low][right]++;
      matrix[right][low]++;
      right--;
    }
    if (low == right) {
      flag = 1;
    } 
    else if (a[low] > a[right]) {
      int temp;
      temp = a[low];
      a[low] = a[right];
      a[right] = temp;
      low = right;
    }
    if (flag != 1) {
      while (a[low] >= a[left] && (low != left)) {
        matrix[left][low]++;
        matrix[low][left]++;
        left++;
      }
      if (low == left) {
        flag = 1;
      } else if (a[low] < a[left]) {
        int temp;
        temp = a[low];
        a[low] = a[left];
        a[left] = temp;
        low = left;
      }
    }
  }
  return low;
}
