//
// Created by user on 09-Jun-18.
//

#include "game.h"

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


