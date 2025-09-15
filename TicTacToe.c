#include <stdio.h>

void initializeBoard(int N, char board[N][N]);
void displayBoard(int N, char board[N][N]);

int main() {
    int N;
1
    printf("Enter board size (3-10): ");
    scanf("%d", &N);

    if (N < 3 || N > 10) {
        printf("Invalid board size!\n");
        return 1;
    }

    char board[N][N];

    initializeBoard(N, board);
    displayBoard(N, board);

    return 0;
}

void initializeBoard(int N, char board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = '-';
        }
    }
}

void displayBoard(int N, char board[N][N]) {
    printf("\nCurrent Board:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf(" %c ", board[i][j]);
        }
        printf("\n");
    }
}