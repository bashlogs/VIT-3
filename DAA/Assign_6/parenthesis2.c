#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateParenthesis(int n) {
    
    char **pattern = (char **)malloc(1000 * sizeof(char *));
    for (int i = 0; i < 1000; i++) {
        pattern[i] = (char *)malloc((2 * n + 1) * sizeof(char));
    }

    sprintf(pattern[0], "%c", '(');
    int count = 1;

    for (int i = 1; i < 2 * n; i++) {
        int curCount = count;
        for (int j = 0; j < curCount; j++) {
            char *cur = pattern[j];
            int open = 0, close = 0;
            for (int k = 0; k < strlen(cur); k++) {
                if (cur[k] == '(') {
                    open++;
                } else if (cur[k] == ')') {
                    close++;
                }
            }

            if (open < n) {
                sprintf(pattern[count], "%s%c", cur, '(');
                count++;
            }

            if (close < open) {
                sprintf(pattern[j], "%s%c", cur, ')');
            }
        }
    }

    for (int i = 0; i < count; i++) {
        if (strlen(pattern[i]) == 2 * n) {
            printf("%s\n", pattern[i]);
            free(pattern[i]);
        }
    }
    free(pattern);
}

int main() {
    int n;
    printf("Enter the number: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input.\n");
    } else {
        generateParenthesis(n);
    }

    return 0;
}
