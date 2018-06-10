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
    // check if player already exists
    for(int i = 0; i < maxPlayers; i++){
        if((playersArr[i] != nullptr) && (*playersArr[i]).isPlayer(playerName))
        {
            return NAME_ALREADY_EXISTS;
        }
    }

    // find empty spot in array for player
    int players_num = maxPlayers;
    for(int i = 0; i < maxPlayers; i++){
        if(playersArr[i] == nullptr){
            players_num = i;
            break;
        }
    }

    // if there is no spot for player in array return game full
    if(players_num >= maxPlayers) return GAME_FULL;

    // add new player to array
     Weapon weapon = {weaponName, target, hit_strength};
     playersArr[players_num] = new Player{playerName, weapon};

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
    // delete spaces in array
    for(int i = 0; i < game.maxPlayers; i++) {
        if(!game.playersArr[i]) {
            int j = i;
            while (!game.playersArr[j] && j < game.maxPlayers) {
                j++;
            }
            game.playersArr[i] = game.playersArr[j];
            game.playersArr[j] = nullptr;
        }
    }

    // sort players array
    for(int i = 0; i < game.maxPlayers && game.playersArr[i]; i++) {
        int min = i;
        for (int j = i; j < game.maxPlayers && game.playersArr[i] ; j++) {
            if (*game.playersArr[j] < *game.playersArr[min]){
                min = j;
            }
        }
        Player* tmp_player = game.playersArr[min];
        game.playersArr[min] = game.playersArr[i];
        game.playersArr[i] = tmp_player;
    }

    // print sorted array
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
            delete playersArr[i];
            removed = true;
        }
    }
    return removed;
}
