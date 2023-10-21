#include <stdbool.h>
#include <stdio.h>

#define MAX_N 20  

void print(int board[MAX_N][MAX_N], int N)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j])
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
}

bool isSafe(int board[MAX_N][MAX_N], int row, int col, int N)
{
    int i, j;

    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

bool solve(int board[MAX_N][MAX_N], int col, int N)
{
    if (col >= N)
        return true;

    for (int i = 0; i < N; i++) {

        if (isSafe(board, i, col, N)) {
            board[i][col] = 1;

            if (solve(board, col + 1, N))
                return true;
            board[i][col] = 0; // BACKTRACK
        }
    }

    return false;
}

bool solveNQ(int N)
{
    int board[MAX_N][MAX_N];

    // Initialize the board
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = 0;
        }
    }

    if (solve(board, 0, N) == false) {
        printf("Solution does not exist\n");
        return false;
    }

    print(board, N);
    return true;
}

int main()
{
    int N;
    printf("Enter the board size for the N-Queens problem: ");
    scanf("%d", &N);

    if (N < 1 || N > MAX_N) {
        printf("Invalid board size. Please enter a number between 1 and %d.\n", MAX_N);
        return 1;
    }

    solveNQ(N);
    return 0;
}
