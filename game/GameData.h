#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "Player.h"
#include "Board.h"

typedef struct {
    Player *p1;
    Player *p2;
    Board *board;
    const Player *active_player;
} GameData;

void init_gamedata(GameData *gamedata, Player *p1, Player *p2, Board *board);
void switchPlayer(GameData *gamedata);

#endif
