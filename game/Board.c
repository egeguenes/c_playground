#include "Board.h"
#include <stdio.h>

void init_board(Board *board, char empty) {
    board->empty = empty;
    for (int i=0; i<BOARD_SIZE; i++) {
        board->board[i] = empty;
    }
}

void placeMark(Board *board, int idx, const Player *player) {
    if (idx < BOARD_SIZE && idx >= 0) {
        board->board[idx] = player->mark;
    }
}

bool gameFinished(const Board *board) {
    for (int i=0; i<3; i++) {
        if ((board->board[0+3*i] == board->board[1+3*i])&&
            (board->board[1+3*i] == board->board[2+3*i])&&
            (board->board[0+3*i] != board->empty)) {
                return true;
            }
        if ((board->board[i] == board->board[i+3])&&
            (board->board[i+3] == board->board[i+6])&&
            (board->board[i] != board->empty)) {
                return true;
            }
    }

    if ((board->board[0] == board->board[4]) && (board->board[4] == board->board[8]) && (board->board[0] != board->empty)) {
        return true;
    }

    if ((board->board[2] == board->board[4]) && (board->board[4] == board->board[6]) && (board->board[2] != board->empty)) {
        return true;
    }

    for (int i=0; i<BOARD_SIZE; i++) {
        if (board->board[i] == board->empty) {
            return false;
        }
    }

    return false;
}

void printBoard(const Board *board) {
    for (int i=0; i<3; i++) {
        printf("%c %c %c\n", board->board[3*i+0], board->board[3*i+1], board->board[3*i+2]);
    }
}
