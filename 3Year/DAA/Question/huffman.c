#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 256

struct Node {
    char data;
    unsigned freq;
    struct Node* left;
    struct Node* right;
};

struct min {
    unsigned size;
    unsigned capacity;
    struct Node** array;
};

struct Node* newNode(char data, unsigned freq) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    node->freq = freq;
    return node;
}

struct min* Heap(unsigned capacity) {
    struct min* min = (struct min*)malloc(sizeof(struct min));
    min->size = 0;
    min->capacity = capacity;
    min->array = (struct Node**)malloc(min->capacity * sizeof(struct Node*));
    return min;
}

void swap(struct Node** a, struct Node** b) {
    struct Node* t = *a;
    *a = *b;
    *b = t;
}

void minify(struct min* min, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < min->size && min->array[left]->freq < min->array[smallest]->freq)
        smallest = left;

    if (right < min->size && min->array[right]->freq < min->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swap(&min->array[idx], &min->array[smallest]);
        minify(min, smallest);
    }
}

int isSizeOne(struct min* min) {
    return (min->size == 1);
}

struct Node* extractMin(struct min* min) {
    struct Node* temp = min->array[0];
    min->array[0] = min->array[min->size - 1];
    --min->size;
    minify(min, 0);
    return temp;
}

void insertmin(struct min* min, struct Node* node) {
    ++min->size;
    int i = min->size - 1;
    while (i && node->freq < min->array[(i - 1) / 2]->freq) {
        min->array[i] = min->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    min->array[i] = node;
}

void buildmin(struct min* min) {
    int n = min->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minify(min, i);
}

struct Node* build(char data[], int freq[], int size) {
    struct Node *left, *right, *top;
    struct min* min = Heap(size);

    for (int i = 0; i < size; ++i)
        insertmin(min, newNode(data[i], freq[i]));

    buildmin(min);

    while (!isSizeOne(min)) {
        left = extractMin(min);
        right = extractMin(min);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertmin(min, top);
    }

    return extractMin(min);
}

void printTree(struct Node* root, int level) {
    if (root == NULL)
        return;

    printTree(root->left, level + 1);
    
    for (int i = 0; i < level; i++)
        printf("\t");
    
    if (root->data != '$')
        printf("(%c-%d)\n", root->data, root->freq);
    else
        printf("($-%d)\n", root->freq);

    printTree(root->right, level + 1);
}


int main() {
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    int freq[] = {10, 8, 20, 12, 42, 3, 5};
    int size = sizeof(data) / sizeof(data[0]);

    struct Node* root = build(data, freq, size);

    printf("Huffman Tree:\n");
    printTree(root, 0);

    return 0;
}
