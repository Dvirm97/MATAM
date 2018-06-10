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
        if (playersArr[i] != nullptr)
            delete playersArr[i];
    }
    delete[] playersArr;
}
GameStatus Game::addPlayer(const char* playerName, const char* weaponName,
<<<<<<< HEAD
                                   Target target, int hit_strength){
    // check if player already exists
    for(int i = 0; i < maxPlayers; i++){
        if((playersArr[i] != nullptr) && (*playersArr[i]).isPlayer(playerName))
        {
            return NAME_ALREADY_EXISTS;
        }
    }

    // find empty spot in array for player
=======
                           Target target, int hit_strength){
>>>>>>> a0cce6fb57ad0871f9d9a1c2992ab2979df863f7
    int players_num = maxPlayers;
    for(int i = 0; i < maxPlayers; i++){
        if(playersArr[i] == nullptr){
            players_num = i;
            break;
        }
    }

    // if there is no spot for player in array return game full
    if(players_num >= maxPlayers) return GAME_FULL;

<<<<<<< HEAD
    // add new player to array
     Weapon weapon = {weaponName, target, hit_strength};
     playersArr[players_num] = new Player{playerName, weapon};
=======
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
>>>>>>> a0cce6fb57ad0871f9d9a1c2992ab2979df863f7

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
<<<<<<< HEAD
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
=======
>>>>>>> a0cce6fb57ad0871f9d9a1c2992ab2979df863f7
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
<<<<<<< HEAD
=======
            cout << *(playersArr[i]) << endl;
>>>>>>> a0cce6fb57ad0871f9d9a1c2992ab2979df863f7
            delete playersArr[i];
            removed = true;
        }
    }
    return removed;
}
GameStatus Game::fight(const char* playerName1, const char* playerName2) {
    Player* player1 = findPlayer(playerName1);
    if (player1 == nullptr) return NAME_DOES_NOT_EXIST;
    Player* player2 = findPlayer(playerName2);
    if (player2 == nullptr) return NAME_DOES_NOT_EXIST;

    if (!player1->fight(*player2)) return FIGHT_FAILED;

    if(!player1->isAlive())
        removePlayer(playerName1);
    if(!player2->isAlive())
        removePlayer(playerName2);
    return SUCCESS;
}

Player* Game::findPlayer(const char* playerName) {
    for (int i=0; i < maxPlayers; i++) {
        if (playersArr[i] && playersArr[i]->isPlayer(playerName))
            return playersArr[i];
    }
    return nullptr;
}

void Game::removePlayer(const char* playerName) {
    for (int i=0; i < maxPlayers; i++) {
        if (playersArr[i] && playersArr[i]->isPlayer(playerName)) {
            delete playersArr[i];
            playersArr[i] = nullptr;
        }
    }
}
