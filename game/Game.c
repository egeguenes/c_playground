#include "Game.h"
#include <stdio.h>

void init_game(Game *game) {
    Player *p1 = game->gamedata.p1;
    Player *p2 = game->gamedata.p2;
    Board *board = game->gamedata.board;

    p1->mark = 'x';
    p2->mark = 'o';
    init_board(board, '-');
    init_gamedata(&game->gamedata, *p1, *p2, *board);
}

void run(Game *game) {
    gameLoop(game);
    endGame(game);
}

void turn(Game *game) {
    printBoard(game->gamedata.board);
    markBoard(game);
    switchPlayer(&game->gamedata);
}

void gameLoop(Game *game) {
    while (!gameFinished(game->gamedata.board)) {
        turn(game);
    }
}

void markBoard(Game *game) {
    printf("Input of player %d: \n", (game->gamedata.active_player == game->gamedata.p1) ? 1 : 2);
}
int queryInput(Game *game);
void endGame(Game *game);

char getCharInput() {
    char input[3];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return '\0';
    }

    if (input[1] != '\n' && input[1] != '\0') {
        while(getchar() != '\n');
        return '\n';
    }

    return input[0];
}
