#ifndef BOARD_H
#define BOARD_H

#include "Player.h"
#include <stdbool.h>
#define BOARD_SIZE 9

typedef struct {
    char empty;
    char board[BOARD_SIZE];
} Board;

void init_board(Board *board, char emtpy);
void placeMark(Board *board, int idx, const Player *player);
bool gameFinished(const Board *board);
void printBoard(const Board *board);

#endif
