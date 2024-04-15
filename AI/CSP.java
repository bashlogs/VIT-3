import java.util.Scanner;

public class CSP {
    static int solutionCount = 0;
    static int n;
    static int[][] chessboard;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter size of chess board: ");
        n = scanner.nextInt();
        chessboard = new int[n][n];
        solveNQueens(0);
        System.out.println("Total solutions: " + solutionCount);
        scanner.close();
    }

    public static void printChessboard() {
        for (int[] row : chessboard) {
            for (int col : row) {
                System.out.print(col == 1 ? "Q " : ". ");
            }
            System.out.println();
        }
        System.out.println("-----------------");
    }

    public static boolean isSafe(int row, int col) {
        // Check horizontal positions
        for (int i = col; i >= 0; i--) {
            if (chessboard[row][i] == 1) return false;
        }

        int i = row, j = col;

        // Check the upper left diagonal
        while (i >= 0 && j >= 0) {
            if (chessboard[i][j] == 1) return false;
            i--;
            j--;
        }

        i = row;
        j = col;

        // Check the lower left diagonal
        while (i < n && j >= 0) {
            if (chessboard[i][j] == 1) return false;
            i++;
            j--;
        }

        return true;
    }

    public static void solveNQueens(int currentColumn) {
        if (currentColumn >= n) return;

        for (int row = 0; row < n; row++) {
            if (isSafe(row, currentColumn)) {
                chessboard[row][currentColumn] = 1;
                if (currentColumn == n - 1) {
                    printChessboard();
                    solutionCount++;
                }
                solveNQueens(currentColumn + 1);
                chessboard[row][currentColumn] = 0; // Backtracking
            }
        }
    }
}

