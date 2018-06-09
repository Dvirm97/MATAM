#include "Game.h"

Game::Game(int maxPlayers) {
    this->maxPlayers = maxPlayers;
    this->playersArr = new Player*[maxPlayers];
    for (int i=0; i < maxPlayers; i++) {
        playersArr[i] = nullptr;
    }
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
    int players_num = maxPlayers;
    for(int i = 0; i < maxPlayers; i++){
        if(playersArr[i] == nullptr){
            players_num = i;
            break;
        }
        if((*playersArr[i]).isPlayer(playerName)) {
            return NAME_ALREADY_EXISTS;
        }
    }

    if(players_num >= maxPlayers) return GAME_FULL;

     Weapon weapon = {weaponName, target, hit_strength};
     playersArr[players_num] = new Player{playerName, weapon};
    
    // sort players array
    for(int i = 0; i <= players_num; i++) {
        int min = i;
        for (int j = i; j <= players_num; j++) {
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
    for(int i = 0; i < game.maxPlayers; i++){
        if(game.playersArr[i] == nullptr){
            break;
        }
        os << "player " << i << ": " << *(game.playersArr[i]) << endl;
    }
    return os;
}
bool Game::removeAllPlayersWithWeakWeapon(int weaponStrength) {
    bool removed = false;
    for (int i=0; i < maxPlayers; i++) {
        if(playersArr[i] && playersArr[i]->weaponIsWeak(weaponStrength)) {
            //cout << *(playersArr[i]) << endl;
            delete playersArr[i];
            playersArr[i] = nullptr;
            removed = true;
        }
    }
    return removed;
}
