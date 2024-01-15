#include <stdio.h>
#include <stdlib.h>

void quick_sort(int a[], int, int);
int partition(int a[], int, int);
int **matrix;

int main() {
  int n;
  printf("Enter no. of element: ");
  scanf("%d", &n);
  int arr[n];

  printf("Enter the elements: ");
  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  matrix = (int **)malloc(n * sizeof(int *));
  for (int i = 0; i < n; i++) {
    matrix[i] = (int *)malloc(n * sizeof(int));
    for (int j = 0; j < n; j++) {
      matrix[i][j] = 0;
    }
  }

  quick_sort(arr, 0, n - 1);

  printf("\nSorted Array: ");
  for (int i = 0; i < n; i++) {
    printf("%d\t", arr[i]);
  }

  printf("\n\nThe number of comparisons made are as follows: \n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }

  // Free allocated memory
  for (int i = 0; i < n; i++) {
    free(matrix[i]);
  }
  free(matrix);

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
  int low = i, right = j, left = i, flag = 0;
  while (flag != 1) {

    while ((a[low] <= a[right]) && (low != right)) {
      matrix[a[low]][a[right]]++;
      matrix[a[right]][a[low]]++;
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
        matrix[a[left]][a[low]]++;
        matrix[a[low]][a[left]]++;
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
