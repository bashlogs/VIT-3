#include <stdio.h>
#include <stdlib.h>

void quick_sort(int a[], int, int);
int partition(int a[], int, int);
int **matrix;

int main() {
  int n;
  printf("Enter the number of elements in the array: ");
  scanf("%d", &n);
  int arr[n];

  printf("Enter the elements of the array: ");
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

  printf("\nThe array received after implementing Quick Sort is\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t", arr[i]);
  }

  printf("\n\nThe number of comparisons made are as follows\n");
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

void quick_sort(int a[], int beg, int end) {
  int loc;
  if (beg < end) {
    loc = partition(a, beg, end);
    quick_sort(a, beg, loc - 1);
    quick_sort(a, loc + 1, end);
  }
}

int partition(int a[], int beg, int end) {
  int loc = beg, right = end, left = beg, flag = 0;
  while (flag != 1) {
    while ((a[loc] <= a[right]) && (loc != right)) {
      matrix[loc][right]++;
      matrix[right][loc]++;
      right--;
    }
    if (loc == right) {
      flag = 1;
    } else if (a[loc] > a[right]) {
      int temp;
      temp = a[loc];
      a[loc] = a[right];
      a[right] = temp;
      loc = right;
    }
    if (flag != 1) {
      while (a[loc] >= a[left] && (loc != left)) {
        matrix[left][loc]++;
        matrix[loc][left]++;
        left++;
      }
      if (loc == left) {
        flag = 1;
      } else if (a[loc] < a[left]) {
        int temp;
        temp = a[loc];
        a[loc] = a[left];
        a[left] = temp;
        loc = left;
      }
    }
  }
  return loc;
}
