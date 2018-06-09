#include "Player.h"

#ifndef HW4_GAME_H
#define HW4_GAME_H


class Game {
    int maxPlayers;
    Player** playersArr;
public:
    explicit Game(int maxPlayers);
    ~Game();
};
#endif //HW4_GAME_H
