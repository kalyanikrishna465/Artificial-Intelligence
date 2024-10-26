#include <stdio.h>
#include <stdlib.h>
#define SIZE 3

void printBoard(int board[SIZE][SIZE]);
int isSolved(int board[SIZE][SIZE]);
void makeMove(int board[SIZE][SIZE], int move);
int findZero(int board[SIZE][SIZE], int *zeroX, int *zeroY);
void swap(int *a, int *b);
void inputBoard(int board[SIZE][SIZE]);

int main() {
    int board[SIZE][SIZE];
    int move;
    int zeroX, zeroY;
    int steps = 0;

    printf("Welcome to the 8-puzzle game!\n");
    printf("Please enter the initial configuration of the board (0 for empty space):\n");
    inputBoard(board);

    int zeroCount = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) zeroCount++;
        }
    }
    if (zeroCount != 1) {
        printf("Invalid board configuration. It must contain exactly one empty space (0).\n");
        return 1;
    }

    while (!isSolved(board)) {
        printBoard(board);
        int validInput = 0;

        while (!validInput) {
            printf("Enter move (1 = Up, 2 = Down, 3 = Left, 4 = Right): ");
            if (scanf("%d", &move) != 1) {
                printf("Invalid input. Please enter a number.\n");
                while (getchar() != '\n');
                continue;
            }
            if (move < 1 || move > 4) {
                printf("Invalid move. Please enter a number between 1 and 4.\n");
            } else {
                validInput = 1;
            }
        }

        if (findZero(board, &zeroX, &zeroY)) {
            makeMove(board, move);
            steps++;
        } else {
            printf("Error finding empty space.\n");
        }
    }

    printBoard(board);
    printf("Congratulations! You've solved the puzzle in %d steps!\n", steps);
    return 0;
}

void printBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                printf("  ");
            } else {
                printf("%2d ", board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int isSolved(int board[SIZE][SIZE]) {
    int correct[SIZE][SIZE] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != correct[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

void makeMove(int board[SIZE][SIZE], int move) {
    int zeroX, zeroY;
    if (!findZero(board, &zeroX, &zeroY)) {
        printf("Error finding empty space.\n");
        return;
    }
    int newX = zeroX, newY = zeroY;
    switch (move) {
        case 1:
            newX--;
            break;
        case 2:
            newX++;
            break;
        case 3:
            newY--;
            break;
        case 4:
            newY++;
            break;
    }
    if (newX < 0 || newX >= SIZE || newY < 0 || newY >= SIZE) {
        printf("Move out of bounds.\n");
        return;
    }
    swap(&board[zeroX][zeroY], &board[newX][newY]);
}

int findZero(int board[SIZE][SIZE], int *zeroX, int *zeroY) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                *zeroX = i;
                *zeroY = j;
                return 1;
            }
        }
    }
    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void inputBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            while (1) {
                printf("Enter value for cell (%d, %d): ", i, j);
                if (scanf("%d", &board[i][j]) != 1) {
                    printf("Invalid input. Please enter an integer.\n");
                    while (getchar() != '\n');
                } else if (board[i][j] < 0 || board[i][j] > 8) {
                    printf("Invalid value. Enter a number between 0 and 8.\n");
                } else {
                    break;
                }
            }
        }
    }
}
