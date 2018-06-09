#include "Game.h"

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
GameStatus Game::addPlayer(const char* playerName, const char* weaponName,
                           Target target, int hit_strength){
    int count = 0;
    while(this->playersArr[count]){
        if((*this->playersArr[count]).isPlayer(playerName)) {
            return NAME_ALREADY_EXISTS;
        }
        count++;
    }

    if(count >= this->maxPlayers) return GAME_FULL;

    *this->playersArr[count] = {playerName, {weaponName, target, hit_strength}};

    // sort players array
    for(int i = 0; i <= count; i++) {
        int min = i;
        for (int j = i; j <= count; j++) {
            if (*playersArr[j] < *playersArr[min]){
                min = j;
            }
        }
        Player tmp_player = *playersArr[i];
        *playersArr[i] = *playersArr[min];
        *playersArr[min] = tmp_player;
    }

    return SUCCESS;
}
GameStatus Game::nextLevel(const char* playerName){
    for(int i = 0; i < this->maxPlayers; i++){
        if((*this->playersArr[i]).isPlayer(playerName)){
            (*this->playersArr[i]).nextLevel();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}
GameStatus Game::makeStep(const char* playerName){
    for(int i = 0; i < this->maxPlayers; i++){
        if((*this->playersArr[i]).isPlayer(playerName)){
            (*this->playersArr[i]).makeStep();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}
GameStatus Game::addLife(const char* playerName){
    for(int i = 0; i < this->maxPlayers; i++){
        if((*this->playersArr[i]).isPlayer(playerName)){
            (*this->playersArr[i]).addLife();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}
GameStatus Game::addStrength(const char* playerName, int strengthToAdd){
    if(strengthToAdd < 0) return INVALID_PARAM;
    for(int i = 0; i < this->maxPlayers; i++){
        if((*this->playersArr[i]).isPlayer(playerName)){
            (*this->playersArr[i]).addStrength(strengthToAdd);
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXIST;
}
ostream& operator<<(ostream& os, const Game& game){
    int i = 0;
    while(game.playersArr[i]){
        //os << "player " << i << ": " << *(game.playersArr[i]) << endl;
        i++;
    }
    return os;
}
