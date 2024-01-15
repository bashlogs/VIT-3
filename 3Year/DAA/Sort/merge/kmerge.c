#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int value;
    int subarrayIdx;
    int elementIdx;
} data;

void swap(data *a, data *b)
{
    data temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(data arr[], int size, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && arr[left].value < arr[smallest].value)
    {
        smallest = left;
    }

    if (right < size && arr[right].value < arr[smallest].value)
    {
        smallest = right;
    }

    if (smallest != i)
    {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, size, smallest);
    }
}

void buildMinHeap(data arr[], int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        minHeapify(arr, size, i);
    }
}

void kMergeSort(int arr[], int n, int k)
{
    if (n <= 1)
    {
        return;
    }

    if (k > n)
    {
        k = n;
    }

    int subarraySize = n / k;
    int lastSize = subarraySize + n % k;

    int **subarrays = malloc(k * sizeof(int *));
    int *subarraySizes = calloc(k, sizeof(int));

    for (int i = 0; i < k - 1; i++)
    {
        subarrays[i] = malloc(subarraySize * sizeof(int));
        subarraySizes[i] = subarraySize;

        for (int j = 0; j < subarraySize; j++)
        {
            subarrays[i][j] = arr[i * subarraySize + j];
        }
    }

    subarrays[k - 1] = malloc(lastSize * sizeof(int));
    subarraySizes[k - 1] = lastSize;

    for (int j = 0; j < lastSize; j++)
    {
        subarrays[k - 1][j] = arr[(k - 1) * subarraySize + j];
    }

    for (int i = 0; i < k; i++)
    {
        kMergeSort(subarrays[i], subarraySizes[i], k);
    }

    data *heap = malloc(k * sizeof(data));
    int size = 0;

    for (int i = 0; i < k; i++)
    {
        if (subarraySizes[i] > 0)
        {
            heap[size].value = subarrays[i][0];
            heap[size].subarrayIdx = i;
            heap[size].elementIdx = 0;
            size++;
        }
    }

    buildMinHeap(heap, size);

    int mergeIndex = 0;

    while (size > 0)
    {
        data min = heap[0];
        arr[mergeIndex] = min.value;
        mergeIndex++;

        int subarrayIdx = min.subarrayIdx;
        int elementIdx = min.elementIdx + 1;

        if (elementIdx < subarraySizes[subarrayIdx])
        {
            heap[0].value = subarrays[subarrayIdx][elementIdx];
            heap[0].elementIdx = elementIdx;
        }
        else
        {
            heap[0] = heap[size - 1];
            size--;
        }

        minHeapify(heap, size, 0);
    }

    for (int i = 0; i < k; i++)
    {
        free(subarrays[i]);
    }

    free(subarrays);
    free(subarraySizes);
    free(heap);
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int nums, k;

    printf("How much number you want to enter: ");
    scanf("%d", &nums);

    int arr[nums];

    printf("Enter the numbers: ");
    for (int i = 0; i < nums; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter the value of k: ");
    scanf("%d", &k);

    kMergeSort(arr, nums, k);

    printf("\nSorted array: ");
    printArray(arr, nums);

    return 0;
}