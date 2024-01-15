#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

typedef struct 
{ 
    char **data; 
    size_t size; 
    size_t capacity;
} node;

void create(node *p) 
{ 
    p->data = NULL;
    p->size = 0;
    p->capacity = 0;
}

void push(node *p, const char *str) 
{ 
    if (p->size >= p->capacity) 
    {
        size_t newCapacity = (p->capacity == 0) ? 1 : p->capacity * 2;
        char **newData = (char **)realloc(p->data, newCapacity * sizeof(char *)); 
        if (newData == NULL) {
            fprintf(stderr, "Memory allocation failed\n"); 
            exit(EXIT_FAILURE);
        }
        p->data = newData;
        p->capacity = newCapacity;
    }

    p->data[p->size] = strdup(str); 
    if (p->data[p->size] == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n"); 
        exit(EXIT_FAILURE);
    }
    p->size++;
}

void pfree(node *p) 
{
    for (size_t i = 0; i < p->size; i++) 
    { 
        free(p->data[i]);
    }
    free(p->data); 
    p->data = NULL; 
    p->size = 0;
    p->capacity = 0;
}

node generateParenthesis(int n) 
{ 
    node dp[n + 1]; 
    create(&dp[0]); 
    push(&dp[0], "");

    for (int i = 1; i <= n; i++) 
    { 
        create(&dp[i]);
        for (int j = 0; j < i; j++) 
        { 
            node left = dp[j];
            node right = dp[i - j - 1];
            for (size_t l = 0; l < left.size; l++) {
                for (size_t r = 0; r < right.size; r++) 
                { 
                    char pattern[2 * n + 1];
                    sprintf(pattern, "(%s)%s", left.data[l], right.data[r]); 
                    push(&dp[i], pattern);
                }
            }
        }
    }
    return dp[n];
}

int main() {
    int n;
    printf("Enter the number: "); 
    scanf("%d", &n);

    node patterns = generateParenthesis(n);

    for (size_t i = 0; i < patterns.size; i++) {
        printf("%s\n", patterns.data[i]);
    }

    for (int i = 0; i <= n; i++) 
    { 
        pfree(&patterns);
    }

    return 0;
}

