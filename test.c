#include <stdio.h>
char board[3][3];   // 3x3 tic-tac-toe board

void initBoard() {
    int i, j, num = '1';
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            board[i][j] = num++;  // fill 1..9
        }
    }
}

void printBoard() {
    int i;
    for (i = 0; i < 3; i++) {
        printf(" --- --- --- \n");
        printf("| %c | %c | %c |\n", board[i][0], board[i][1], board[i][2]);
    }
    printf(" --- --- --- \n");
}

void check(char n, char input) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (board[i][j] == n) {
                board[i][j] = input;
                return;  // stop once placed
            }
        }
    }
}

int main() {
    char move;
    initBoard();   // ✅ make sure board is initialized
    printBoard();
    printf("Enter move for X: ");
    scanf(" %c", &move);
    check(move, 'X');
    printBoard();
    printf("Enter move for O: ");
    scanf(" %c", &move);
    check(move, 'O');
    printBoard();
    return 0;
}
