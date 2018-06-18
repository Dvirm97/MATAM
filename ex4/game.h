#include "Player.h"

#ifndef HW4_GAME_H
#define HW4_GAME_H

enum GameStatus{
    INVALID_PARAM,
    NAME_ALREADY_EXISTS,
    GAME_FULL,
    NAME_DOES_NOT_EXIST,
    FIGHT_FAILED,
    SUCCESS
};

class Game {
    int maxPlayers;
    Player** players;

public:
    /**
    * Constructor:   creates a new game
    * @param maxPlayers - The maximum amount of players allowed for this game
    *                    type int
    */
    explicit Game(int maxPlayers);

    /**
    * Destructor:  destroys the game.
    */
    ~Game();

    /**
    * Copy Constructor: copies a game
    * @param game - game to copy. type const Game&
    */
    Game(const Game& game);

    /**
    * Opertor =: overloads the operator '=' for type game
    * @param game - game to copy. type const Game&
    */
    Game& operator=(const Game& game);

    /**
     * Operator <<: overloading printing operator for printing a game
     *         prints all the players in the game in lexicorgraphic order
     *    output format:
     *        player 0: <player>,
     *               ...
     *        player <num>: <player>,
    */
    friend ostream& operator<<(ostream& os, const Game& game);

    /**
    * addPlayer:  adds a player to the game
    * @param playerName - The name of the player. type const char*
    * @param weaponName - The name of the weapon. type const char*
    * @param target - The target the weapon. an enum value of Target
    * @param hit_strength - The basic amount of strength the weapon hits.
    *                       Of type int.
    * return NAME_ALREADY_EXISTS    if name already exists
    *        GAME_FULL      game reached maximus num of players
    *        SUCCESS       if added successfully
    */
    GameStatus addPlayer(const char* playerName, const char* weaponName,
                         Target target, int hit_strength);

    /**
   * nextLevel:  brings a player level up
   * @param playerName - The name of the player to level up. type const char*
   * return NAME_DOES_NOT_EXIST    if name does not exist
   *        SUCCESS       if leveled up successfully
   */
    GameStatus nextLevel(const char* playerName);

    /**
   * makeStep:  brings a player a step forward
   * @param playerName - The name of the player to step forward.
   *                    type const char*
   * return NAME_DOES_NOT_EXIST    if name does not exist
   *        SUCCESS       if steped forward successfully
   */
    GameStatus makeStep(const char* playerName);

    /**
   * addLife: add life to player
   * @param playerName - The name of the player to add life to. type const char*
   * return NAME_DOES_NOT_EXIST    if name does not exist
   *        SUCCESS                if life added successfully
   */
    GameStatus addLife(const char* playerName);

    /**
  * addStrength: add strength to player
  * @param playerName - The name of the player to add strength to.
  *                     type const char*
  * @param strengthToAdd - sterngth to add to player. type int
  * return NAME_DOES_NOT_EXIST    if name does not exist
  *        INVALID_PARAM          if strengthToAdd is negative
  *        SUCCESS                if life strength successfully
  */
    GameStatus addStrength(const char* playerName, int strengthToAdd);

    /**
   * removeAllPlayersWithWeakWeapon:  remove from array all players with weapon
   *                                  hit value which is under certain value.
   * @param weaponStrength - the minimum value a weapon hit value can be.
   *                              Of type int.
   * return: true - players were removed.
   *         false - players were not removed.
   */
    bool removeAllPlayersWithWeakWeapon(int weaponStrength);

    /**
   * fight: makes a fight between two players and removes a player if died.
   * @param playerName1 - first player in fight. of type const char*
   * @param playerName2 - second player in fight. of type const char*
   * return NAME_DOES_NOT_EXIST    if one of the name does not exist
   *        FIGHT_FAILED           if two players cannot fight
   *        SUCCESS                if life strength successfully
   */
    GameStatus fight(const char* playerName1, const char* playerName2);

private:
    /**
    * findPlayer: searches for a player in the array
    * @param playerName - the player we are searching for. of type const char*
    * return a pointer to the player or null if the player does not exist
    */
    Player* findPlayer(const char* playerName);

    /**
    * removePlayer: removes a player from the array
    * @param playerName - the player we want to remove. of type const char*
    */
    void removePlayer(const char* playerName);

    /**
    * sortPlayers: sorts the players in the array by lexichographical order
    */
    void sortPlayers() const;

    /**
   * condensePlayers: moves all of the players to the begging of the array and
   *                  pushes all of the null pointers to the end of the array.
   */
    bool condensePlayers() const;
};
#endif //HW4_GAME_H
