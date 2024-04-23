import java.util.Scanner;
import java.util.Random;

public class PvC {
    static int[] board = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    static Scanner scanner = new Scanner(System.in);

    public static void showBoard() {
        System.out.println(" " + convertToSymbol(board[0]) + " | " + convertToSymbol(board[1]) + " | " + convertToSymbol(board[2]));
        System.out.println("-----------");
        System.out.println(" " + convertToSymbol(board[3]) + " | " + convertToSymbol(board[4]) + " | " + convertToSymbol(board[5]));
        System.out.println("-----------");
        System.out.println(" " + convertToSymbol(board[6]) + " | " + convertToSymbol(board[7]) + " | " + convertToSymbol(board[8]));
        System.out.println();
    }

    public static String convertToSymbol(int value) {
        if (value == 1) {
            return "X";
        } else if (value == 2) {
            return "O";
        } else {
            return " ";
        }
    }

    public static void go(int index, int turn) {
        board[index] = (turn % 2 != 0) ? 1 : 2;
    }

    public static int possWin(int player) {
        if (player == 1) {
            for (int i = 0; i < 9; i += 3) {
                if (board[i] * board[i + 1] * board[i + 2] == 1) {
                    if (board[i] == 0)
                        return i;
                    if (board[i + 1] == 0)
                        return i + 1;
                    if (board[i + 2] == 0)
                        return i + 2;
                }
            }

            for (int i = 0; i < 3; i++) {
                if (board[i] * board[i + 3] * board[i + 6] == 1) {
                    if (board[i] == 0)
                        return i;
                    if (board[i + 3] == 0)
                        return i + 3;
                    if (board[i + 6] == 0)
                        return i + 6;
                }
            }

            if (board[0] * board[4] * board[8] == 1) {
                if (board[0] == 0)
                    return 0;
                if (board[4] == 0)
                    return 4;
                if (board[8] == 0)
                    return 8;
            }

            if (board[2] * board[4] * board[6] == 1) {
                if (board[2] == 0)
                    return 2;
                if (board[4] == 0)
                    return 4;
                if (board[6] == 0)
                    return 6;
            }
        }
        if (player == 2) {
            for (int i = 0; i < 9; i += 3) {
                if (board[i] * board[i + 1] * board[i + 2] == 8) {
                    if (board[i] == 0)
                        return i;
                    if (board[i + 1] == 0)
                        return i + 1;
                    if (board[i + 2] == 0)
                        return i + 2;
                }
            }

            for (int i = 0; i < 3; i++) {
                if (board[i] * board[i + 3] * board[i + 6] == 8) {
                    if (board[i] == 0)
                        return i;
                    if (board[i + 3] == 0)
                        return i + 3;
                    if (board[i + 6] == 0)
                        return i + 6;
                }
            }

            if (board[0] * board[4] * board[8] == 8) {
                if (board[0] == 0)
                    return 0;
                if (board[4] == 0)
                    return 4;
                if (board[8] == 0)
                    return 8;
            }

            if (board[2] * board[4] * board[6] == 8) {
                if (board[2] == 0)
                    return 2;
                if (board[4] == 0)
                    return 4;
                if (board[6] == 0)
                    return 6;
            }
        }
        return -1;
    }

    public static int make2() {
        if (board[5] == 0) {
            return 5;
        } else {
            int[] options = {2, 4, 6, 8};
            Random rand = new Random();
            int index = rand.nextInt(4); // Generates a random index (0 to 3)
            return options[index];
        }
    }

    public static boolean checkWinner(int player) {
        for (int i = 0; i < 9; i += 3) {
            if (board[i] * board[i + 1] * board[i + 2] == player * player * player)
                return true;
        }

        for (int i = 0; i < 3; i++) {
            if (board[i] * board[i + 3] * board[i + 6] == player * player * player)
                return true;
        }

        if (board[0] * board[4] * board[8] == player * player * player)
            return true;

        return board[2] * board[4] * board[6] == player * player * player;
    }

    public static void main(String[] args) {
        showBoard();
        int turn = 1;
        while (turn <= 9) {
            if (turn % 2 != 0) {
                System.out.print("Your turn (X):");
                int playerMove = scanner.nextInt();
                if (playerMove < 1 || playerMove > 9 || board[playerMove - 1] != 0) {
                    System.out.println("Invalid move. Please choose an empty cell (1-9).");
                    continue;
                }
                go(playerMove - 1, turn);
            } else {
                int computerMove;
                if (turn == 1)
                    computerMove = 0;
                else if (turn == 2)
                    computerMove = (board[4] == 0) ? 4 : 1;
                else if (turn == 3)
                    computerMove = (board[8] == 0) ? 8 : 2;
                else if (turn == 4)
                    computerMove = (possWin(1) != -1) ? possWin(1) : make2();
                else if (turn == 5)
                    computerMove = (possWin(1) != -1) ? possWin(1) : ((possWin(2) != -1) ? possWin(2) : (board[7] == 0) ? 7 : 3);
                else if (turn == 6)
                    computerMove = (possWin(2) != -1) ? possWin(2) : ((possWin(1) != -1) ? possWin(1) : make2());
                else if (turn == 7 || turn == 9)
                    computerMove = (possWin(1) != -1) ? possWin(1) : ((possWin(2) != -1) ? possWin(2) : make2());
                else // turn == 8
                    computerMove = (possWin(2) != -1) ? possWin(2) : ((possWin(1) != -1) ? possWin(1) : make2());
                go(computerMove, turn);
            }

            showBoard();

            if (checkWinner(1)) {
                System.out.println("Player X wins!");
                break;
            } else if (checkWinner(2)) {
                System.out.println("Player O wins!");
                break;
            } else if (turn == 9) {
                System.out.println("It's a draw!");
            }

            turn++;
        }
    }
}