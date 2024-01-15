#include <stdio.h>

void print(int n, int d, char* current, int pos, int count) {
    if (count == 0) {
        return;
    }

    if (pos == n) {
        printf("%s\n", current);
        count--;

        return;
    }

    for (int nextDigit = 0; nextDigit < 10; nextDigit++) {
        if (nextDigit != d || current[pos - 1] - '0' != d) {
            current[pos] = nextDigit + '0';
            print(n, d, current, pos + 1, count);
        }
    }
}

void generateDecimalStrings(int n, int d) {
    int dp[n + 1][10];

    for (int i = 0; i < 10; i++) {
        dp[1][i] = 1;
    }

    for (int length = 2; length <= n; length++) {
        for (int i = 0; i < 10; i++) {
            dp[length][i] = 0;
            for (int j = 0; j < 10; j++) {
                if (i != d || j != d) {
                    dp[length][i] += dp[length - 1][j];
                }
            }
        }
    }

    int count = 0;
    for (int i = 0; i < 10; i++) {
        count += dp[n][i];
    }

    char current[n + 1];
    current[n] = '\0';

    int pos = 0;

    for (int i = 0; i < 10; i++) {
        current[0] = i + '0';
        print(n, d, current, pos + 1, count);
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
