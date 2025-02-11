#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    char mark;
} Player;

void init_player(Player *player, char newMark);

#endif
