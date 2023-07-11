#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quicksort3way(int arr[], int low, int high) {
    if (low >= high) {
        return;
    }

    int pivot = arr[low];
    int lt = low;
    int gt = high;
    int i = low;

    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(&arr[i], &arr[lt]);
            i++;
            lt++;
        } else if (arr[i] > pivot) {
            swap(&arr[i], &arr[gt]);
            gt--;
        } else {
            i++;
        }
    }

    quicksort3way(arr, low, lt - 1);
    quicksort3way(arr, gt + 1, high);
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {34, 64, 21, 35, 22, 67, 83, 12, 45, 21, 42};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    quicksort3way(arr, 0, n - 1);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
