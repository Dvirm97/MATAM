/**
 * class Game
 */

#include "Game.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~ PUBLIC FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Constructor
Game::Game(int maxPlayers):
   maxPlayers(maxPlayers), players(new Player*[maxPlayers]) {
    // initialize players array to null pointers
    for (int i=0; i < maxPlayers; i++) {
        players[i] = nullptr;
    }
}
// Destructor
Game::~Game() {
    // delete all players
    for (int i=0; i < maxPlayers; i++) {
        if (players[i])
            delete (players[i]);
    }
    // delete array
    delete[] players;
}
// Copy Constructor
Game::Game(const Game& game):
        maxPlayers(game.maxPlayers),
        players(new Player*[game.maxPlayers]) {
    for (int i = 0; i < maxPlayers; i++) {
        players[i] = game.players[i];
    }
}
// overloading operator '='
Game& Game::operator=(const Game& game){
    // check if already equal
    if (this == &game) return *this;

    // delete all previouse content
    for(int i = 0; i < maxPlayers; i++){
        delete players[i];
    }
    delete[] players;

    // copy all new content to game
    maxPlayers = game.maxPlayers;
    players =  new Player*[maxPlayers];
    for(int i = 0; i < maxPlayers; i++){
        players[i] = game.players[i];
    }

    // return game with new content
    return *this;
}
GameStatus Game::addPlayer(const char* playerName, const char* weaponName,
                                   Target target, int hit_strength){
    // check if player already exists
    if(findPlayer(playerName) != nullptr) return NAME_ALREADY_EXISTS;

    // find empty spot in array for player
    int players_num = maxPlayers;
    for(int i = 0; i < maxPlayers; i++){
        if(players[i] == nullptr){
            players_num = i;
            break;
        }
    }

    // if there is no spot for player in array return game full
    if(players_num >= maxPlayers) return GAME_FULL;

    // add new player to array
     Weapon weapon = {weaponName, target, hit_strength};
     players[players_num] = new Player{playerName, weapon};

    return SUCCESS;
}
GameStatus Game::nextLevel(const char* playerName){
    // find player to level up
    Player* player = findPlayer(playerName);

    // return error if player does not exist
    if(player == nullptr) return NAME_DOES_NOT_EXIST;

    // level up player
    player->nextLevel();
    return SUCCESS;
}
GameStatus Game::makeStep(const char* playerName){
    // find player to step up
    Player* player = findPlayer(playerName);

    // return error if player does not exist
    if(player == nullptr) return NAME_DOES_NOT_EXIST;

    // step up player
    player->makeStep();
    return SUCCESS;
}
GameStatus Game::addLife(const char* playerName){
    // find player to add life to
    Player* player = findPlayer(playerName);

    // return error if player does not exist
    if(player == nullptr) return NAME_DOES_NOT_EXIST;

    // add life to player
    player->addLife();
    return SUCCESS;
}
GameStatus Game::addStrength(const char* playerName, int strengthToAdd){
    // check input
    if(strengthToAdd < 0) return INVALID_PARAM;

    // find player to add strength to
    Player* player = findPlayer(playerName);

    // return error if player does not exist
    if(player == nullptr) return NAME_DOES_NOT_EXIST;

    // add strength to player
    player->addStrength(strengthToAdd);
    return SUCCESS;
}
// overload printing operator
ostream& operator<<(ostream& os, const Game& game){
    // sort players array
    game.sortPlayers();

    // print all players in sorted array
    for(int i = 0; i < game.maxPlayers; i++){
        if(game.players[i] == nullptr){
            break;
        }
        os << "player " << i << ": " << *(game.players[i]) << "," << endl;
    }
    return os;
}
bool Game::removeAllPlayersWithWeakWeapon(int weaponStrength) {
    bool removed = false;

    // go through all players in array
    for (int i=0; i < maxPlayers; i++) {

        // check if player's weapon is weak
        if(players[i] && players[i]->weaponIsWeak(weaponStrength)) {

            // remove player
            delete players[i];
            players[i] = nullptr;
            removed = true; // update that a player was removed
        }
    }

    // return if players were removed or not
    return removed;
}
GameStatus Game::fight(const char* playerName1, const char* playerName2) {
    // find players in array or return error if one of them does'nt exit
    Player* player1 = findPlayer(playerName1);
    if (player1 == nullptr) return NAME_DOES_NOT_EXIST;
    Player* player2 = findPlayer(playerName2);
    if (player2 == nullptr) return NAME_DOES_NOT_EXIST;

    // make fight and return error if fight failed
    if (!player1->fight(*player2)) return FIGHT_FAILED;

    // check if one of the players died and remove it if so
    if(!player1->isAlive())
        removePlayer(playerName1);
    if(!player2->isAlive())
        removePlayer(playerName2);

    return SUCCESS;
}


//~~~~~~~~~~~~~~~~~~~~~~~ PRIVATE FUNCTIONS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Player* Game::findPlayer(const char* playerName) {
   // go through array
    for (int i=0; i < maxPlayers; i++) {
        // check if current player is our player and return it if so
        if (players[i] && players[i]->isPlayer(playerName))
            return players[i];
    }
    // our player does not exist
    return nullptr;
}
void Game::removePlayer(const char* playerName) {
    // go through array
    for (int i=0; i < maxPlayers; i++) {
        // check if current player is our player and remove it if so
        if (players[i] && players[i]->isPlayer(playerName)) {
            delete players[i];
            players[i] = nullptr;
        }
    }
}
bool Game::condensePlayers() const{
    bool not_empty =  false;
    // go through array
    for(int i = 0; i < maxPlayers; i++) {
        int j = i;

        // find the closest existing player in the array to the current cell
        while (j < maxPlayers && !players[j]) {
            j++;
        }

        if(j == i){  // current cell contains a player
            not_empty = true;
            continue;
        } else if(j == maxPlayers) break;  // no players were found
        if(players[j]) {   // a player was found insert it to current cell
            not_empty = true;
            players[i] = players[j];    // insert player to current cell
            players[j] = nullptr;       // put null in players previouse cell
        }
    }

    // return if array is empty or not
    return not_empty;
}
void Game::sortPlayers() const{
    // push all players to start of array or exist if array is empty
    if(!condensePlayers()) return;

    // go through players in array
    for(int i = 0; i < maxPlayers && players[i]; i++) {
        int min = i;

        // find minimal player in the rest of the array
        for (int j = i; j < maxPlayers; j++) {
            if(players[j] == nullptr){
                break;
            } else if (*players[j] < *players[min]){
                min = j;
            }
        }

        // swap current player with minimal player
        Player* tmp_player = players[min];
        players[min] = players[i];
        players[i] = tmp_player;
    }
}