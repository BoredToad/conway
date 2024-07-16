#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BOARD_WIDTH 50
#define BOARD_HEIGHT 50

void print_board(bool board[BOARD_HEIGHT][BOARD_WIDTH]) {
    printf("\e[1;1H\e[2J"); // who came up with ansii codes?
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++){ 
            char c = ' ';
            if (board[i][j])
                c = '#';
            printf("%c, ", c);
        }
        printf("\n");
    }
}

bool get_state(bool board[BOARD_HEIGHT][BOARD_WIDTH], int y, int x) {
    int neighbours = -1;  // yes, I'm too lazy to skip when it checks itself

    for (int i = y - 1; i < y + 2; i++) {
        if (i < 0 || i >= BOARD_HEIGHT) continue;

        for (int j = x - 1; j < x + 2; j++) {
            if (j < 0 || j >= BOARD_WIDTH) continue;
            if (board[i][j]) neighbours++;
        }
    }

    if (!board[y][x]) {
        if (neighbours == 3) return true;
        return false;
    }

    if (neighbours == 2 || neighbours == 3) return true;

    return false;
}

void tick(bool board[BOARD_HEIGHT][BOARD_WIDTH]) {
    bool tmp_board[BOARD_HEIGHT][BOARD_WIDTH];

    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++)
            tmp_board[i][j] = get_state(board, i, j);

    // board = tmp_board; :(
    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++) board[i][j] = tmp_board[i][j];
}

int main(int argc, char* argv[]) {
    bool board[BOARD_HEIGHT][BOARD_WIDTH];
    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++) board[i][j] = rand() % 2;

    for (;;) {
        tick(board);
        print_board(board);
        usleep(500000);
    }

    return 0;
}
