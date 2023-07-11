// Write a program for k-way merge sort.

void mergeSort(int arr[], int l, int r) {
  if (l < r) {

    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
  }
}

void printArray(int arr[], int size) {
  for (int i = 0; i < size; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

int main(){
    printf("Enter the size of the array: ");
    int size;
    scanf("%d",&size);
    int arr[size];
    printf("Enter the elements: ");
    for(int i=0;i<size;i++){
        scanf("%d",&arr[i]);
    }
    printf("\nUnsorted Array: ");
    printArray(arr, size);
    mergeSort(arr, 0, size - 1);

    printf("Sorted array: ");
    printArray(arr, size);
}