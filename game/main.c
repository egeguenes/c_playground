#include "Game.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    Game *game = (Game*)(malloc(sizeof(Game)));
    if (!game) {
        perror("Malloc error");
        free(game);
        exit(1);
    }
    init_game(game);
    run(game);
    free(game);
    exit(0);
}
