#include "Game.h"
#include <stdio.h>
#include <stdlib.h>

void init_game(Game *game) {
    Player *p1 = game->gamedata.p1;
    Player *p2 = game->gamedata.p2;
    Board *board = game->gamedata.board;

    p1->mark = 'x';
    p2->mark = 'o';
    init_board(board, '-');
    init_gamedata(&game->gamedata, p1, p2, board);
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
    int input;
    while ((input = queryInput(game)) != -1) {
        fprintf(stderr, "The field should be more than 0 and less than 8!");
    }
    placeMark(game->gamedata.board, input, game->gamedata.active_player);
}

int queryInput(Game *game) {
    char input[10];
    printf("Field to mark: ");

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return -1;
    }

    char *endptr;
    int number = strtol(input, &endptr, 10);

    if (endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        return -1;
    }

    return number;
}

void endGame(Game *game) {
    printBoard(game->gamedata.board);
    printf("Game has ended!\n");
}
