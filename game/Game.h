#ifndef GAME_H
#define GAME_H

#include "GameData.h"

typedef struct {
    GameData gamedata;
} Game;

void init_game(Game *game);
void run(Game *game);
void gameLoop(Game *game);
void turn(Game *game);
void markBoard(Game *game);
int queryInput(Game *game);
void endGame(Game *game);

#endif
