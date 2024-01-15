#include <stdio.h>

void print(int n, int d, char* current, int pos, int dp[][10]){
    if (pos == n) {
        printf("%s\n", current);
        return;
    }

    int k = current[pos - 1] - '0';

    for (int i = 0; i < 10; i++) {
        if (i != d || k != d) {
            current[pos] = i + '0';
            print(n, d, current, pos + 1, dp);
        }
    }
}

void generateDecimalStrings(int n, int d) {
    int dp[n + 1][10]; 

    for (int i = 0; i < 10; i++) {
        dp[1][i] = 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < 10; j++) {
            dp[i][j] = 0;
            for (int k = 0; k < 10; k++) {
                if (j != d || k != d) {
                    dp[i][j] += dp[i - 1][k];
                }
            }
        }
    }

    char current[n + 1];
    current[n] = '\0';

    int pos = 0;

    for (int j = 0; j < 10; j++) {
        current[0] = j + '0';
        print(n, d, current, pos + 1, dp);
    }
}

int main() {
    int n, d;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    printf("Enter the value of d: ");
    scanf("%d", &d);

    if (n <= 0 || d < 0 || d > 9) {
        printf("Invalid input\n");
        return 1;
    }

    generateDecimalStrings(n, d);

    return 0;
}
