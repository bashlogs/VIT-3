import java.util.Scanner;

public class TicTacToe1 {
    private char[][] board; 
    public char currentPlayer;

    public TicTacToe1() {
        board = new char[3][3];
        currentPlayer = 'x';
        initializeBoard();
    }
    
    public void initializeBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = '-';
            }
        }
    }

    public void printBoard() {
        System.out.println("-------------");
        for (int i = 0; i < 3; i++) {
            System.out.print("| ");
            for (int j = 0; j < 3; j++) {
                System.out.print(board[i][j] + " | ");
            }
            System.out.println("\n-------------");
        }
    }

    public void layout(){
        int a = 1;
        System.out.println("-------------");
        for (int i = 0; i < 3; i++) {
            System.out.print("| ");
            for (int j = 0; j < 3; j++) {
                System.out.print( a + " | ");
                a++;
            }
            System.out.println("\n-------------");
        }
    }

    public boolean isBoardFull() {
        boolean isFull = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                    isFull = false;
                }
            }
        }
        return isFull;
    }

    public void changePlayer() {
        if (currentPlayer == 'x') {
            currentPlayer = 'o';
        } else {
            currentPlayer = 'x';
        }
    }

    public boolean makeMove(int row, int col) {
        if (row >= 0 && col >= 0 && row < 3 && col < 3) {
            if (board[row][col] == '-') {
                board[row][col] = currentPlayer;
                return true;
            }
        }
        return false;
    }

    public boolean checkForWin() {
        return (checkRowsForWin() || checkColumnsForWin() || checkDiagonalsForWin());
    }

    private boolean checkRowsForWin() {
        for (int i = 0; i < 3; i++) {
            if (checkRowCol(board[i][0], board[i][1], board[i][2]) == true) {
                return true;
            }
        }
        return false;
    }

    private boolean checkColumnsForWin() {
        for (int i = 0; i < 3; i++) {
            if (checkRowCol(board[0][i], board[1][i], board[2][i]) == true) {
                return true;
            }
        }
        return false;
    }

    private boolean checkDiagonalsForWin() {
        return ((checkRowCol(board[0][0], board[1][1], board[2][2]) == true) || checkRowCol(board[0][2], board[1][1], board[2][0]) == true);
    }

    private boolean checkRowCol(char c1, char c2, char c3) {
        return ((c1 != '-') && (c1 == c2) && (c2 == c3));
    }

    public int[] getBestMove() {
        int bestScore = -1000;
        int[] move = new int[2];
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                    board[i][j] = 'o';
                    int score = minimax(board, 0, false);
                    board[i][j] = '-';
                    if (score > bestScore) {
                        bestScore = score;
                        move[0] = i;
                        move[1] = j;
                    }
                }
            }
        }
        return move;
    }

    public int minimax(char[][] board, int depth, boolean isMaximizing) {
        if (checkForWin()) {
            return isMaximizing ? -1 : 1;
        } else if (isBoardFull()) {
            return 0;
        }

        if (isMaximizing) {
            int bestScore = -1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == '-') {
                        board[i][j] = 'o';
                        int score = minimax(board, depth + 1, false);
                        board[i][j] = '-';
                        bestScore = Math.max(score, bestScore);
                    }
                }
            }
            return bestScore;
        } else {
            int bestScore = 1000;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == '-') {
                        board[i][j] = 'x';
                        int score = minimax(board, depth + 1, true);
                        board[i][j] = '-';
                        bestScore = Math.min(score, bestScore);
                    }
                }
            }
            return bestScore;
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        TicTacToe1 game = new TicTacToe1();
        System.out.println("Enter the number according to this layout: ");
        game.layout();

        do {
            System.out.println("Current board layout:");
            game.printBoard();
            int row;
            int col;
            int input;
            if (game.currentPlayer == 'x') {
                do {
                    System.out.print("Player " + game.currentPlayer + ", enter empty box no: ");
                    input = scanner.nextInt()-1;
                    row = input/3;
                    col = input%3;
                }
                while (!game.makeMove(row, col));
            } else {
                int[] bestMove = game.getBestMove();
                game.makeMove(bestMove[0], bestMove[1]);
            }
            game.changePlayer();
        }
        while(!game.checkForWin() && !game.isBoardFull());
        if (game.isBoardFull() && !game.checkForWin()) {
            System.out.println("The game was a draw!");
        } else {
            System.out.println("Current board layout:");
            game.printBoard();
            game.changePlayer();
            System.out.println(Character.toUpperCase(game.currentPlayer) + " Wins!");
        }
    }
}