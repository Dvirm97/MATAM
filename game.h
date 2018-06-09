#include "Player.h"
#include "Weapon.h"

#ifndef HW4_GAME_H
#define HW4_GAME_H


class Game {
    int maxPlayers;
    Player** playersArr;
public:
    explicit Game(int maxPlayers);
    ~Game();
};

Game::Game(int maxPlayers) {
    this->maxPlayers = maxPlayers;
    this->playersArr = new Player*[maxPlayers];
}
Game::~Game() {
    for (int i=0; i < maxPlayers; i++) {
        if (playersArr[i])
            delete (playersArr[i]);
    }
    delete[] playersArr;
}


#endif //HW4_GAME_H
