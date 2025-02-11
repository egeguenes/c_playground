#include "GameData.h"

void init_gamedata(GameData *gamedata, Player *p1, Player *p2, Board *board) {
    gamedata->p1 = *p1;
    gamedata->p2 = *p2;
    gamedata->board = *board;
    gamedata->active_player = gamedata->p1;
}

void switchPlayer(GameData *gamedata) {
    gamedata->active_player = (gamedata->active_player  == gamedata->p1) ? gamedata->p2 : gamedata->p1;
}
