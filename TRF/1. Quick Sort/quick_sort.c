#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quicksort(int a[], int p, int q) {
    int i = p;
    int j = q;
    int pivot = (i + j) / 2;

    while (i < j) {
        while (a[i] < a[pivot]) {
            i++;
        }
        while (a[j] > a[pivot]) {
            j--;
        }
        if (i <= j) {
            swap(&a[i], &a[j]);
            i++;
            j--;
        }
    }

    if (p < j) {
        quicksort(a, p, j);
    }
    if (i < q) {
        quicksort(a, i, q);
    }
}

void printarray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int array[] = {34, 64, 21, 35, 22, 67, 83, 12, 45, 21, 42};
    int n = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");
    printarray(array, n);

    quicksort(array, 0, n - 1);

    printf("Sorted array: ");
    printarray(array, n);

    return 0;
}
