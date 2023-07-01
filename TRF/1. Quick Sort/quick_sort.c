#include <stdlib.h>
#include <stdio.h>

void quicksort(int *a, int low, int high) {
    int i = low;
    int j = high;
    int temp;
    int pivot = (low + high) / 2;

    while (i <= j) {
        while (a[i] < a[pivot])
            i++;
        while (a[j] > a[pivot])
            j--;
        if (i <= j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }

    if (low < j) {
        quicksort(a, low, j);
    }
    if (i < high) {
        quicksort(a, i, high);
    }
}

void printarray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int array[] = {32,52,14,12,55,32,15,8,56};
    int n = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");
    printarray(array, n);

    quicksort(array, 0, n - 1);

    printf("Sorted array: ");
    printarray(array, n);

    return 0;
}
