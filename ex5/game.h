#ifndef HW4_GAME_H
#define HW4_GAME_H

#include "Player.h"
#include "Warrior.h"
#include "Wizard.h"
#include "Troll.h"
#include "mtm_exceptions.h"

enum GameStatus{
    ILLEGAL_WEAPON,
    INVALID_PARAM,
    NAME_ALREADY_EXISTS,
    GAME_FULL,
    NAME_DOES_NOT_EXIST,
    FIGHT_FAILED,
    SUCCESS
};

// class for object function
class ifWeakWeapon{
    int weaponStrength;
public:
    // constructor
    explicit ifWeakWeapon(int weaponStrength) :
            weaponStrength(weaponStrength) {}
    // overload () operator
    bool operator() (Player const& player) const {
        return player.weaponIsWeak(weaponStrength);
    }
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
    * @param playerName - The name of the player. type const string
    * @param weaponName - The name of the weapon. type const string
    * @param target - The target the weapon. an enum value of Target
    * @param hit_strength - The basic amount of strength the weapon hits.
    *                       Of type int.
    * return NAME_ALREADY_EXISTS    if name already exists
    *        GAME_FULL      game reached maximum num of players
    *        SUCCESS       if added successfully
    */
    GameStatus addPlayer(const string playerName, const string weaponName,
                         Target target, int hit_strength);

    /**
    * addWarrior:  adds to the game a player of type warrior
    * @param playerName - The name of the player. type const string
    * @param weaponName - The name of the weapon. type const string
    * @param target - The target the weapon. an enum value of Target
    * @param hit_strength - The basic amount of strength the weapon hits.
    *                       Of type int.
    * @param rider - determines whether the warrior is mounted or not.
    *                       Of type bool.
    * return NAME_ALREADY_EXISTS    if name already exists
    *        GAME_FULL      game reached maximum num of players
    *        SUCCESS       if added successfully
    */
    void addWarrior(const string playerName, const string weaponName,
                         Target target, int hit_strength, bool rider);

    /**
    * addWizard:  adds to the game a player of type wizard
    * @param playerName - The name of the player. type const string
    * @param weaponName - The name of the weapon. type const string
    * @param target - The target the weapon. an enum value of Target
    * @param hit_strength - The basic amount of strength the weapon hits.
    *                       Of type int.
    * @param range - The wizard's attack range. Of type int.
    * return NAME_ALREADY_EXISTS    if name already exists
    *        GAME_FULL      game reached maximum num of players
    *        SUCCESS       if added successfully
    */
    void addWizard(const string playerName, const string weaponName,
                          Target target, int hit_strength, int range);

    /**
    * addTroll:  adds to the game a player of type troll
    * @param playerName - The name of the player. type const string
    * @param weaponName - The name of the weapon. type const string
    * @param target - The target the weapon. an enum value of Target
    * @param hit_strength - The basic amount of strength the weapon hits.
    *                       Of type int.
    * @param maxLife - The troll's maximum life. Of type int.
    * return NAME_ALREADY_EXISTS    if name already exists
    *        GAME_FULL      game reached maximum num of players
    *        SUCCESS       if added successfully
    */
    void addTroll(const string playerName, const string weaponName,
                          Target target, int hit_strength, int maxLife);

    /**
   * nextLevel:  brings a player level up
   * @param playerName - The name of the player to level up. type const string
   * return NAME_DOES_NOT_EXIST    if name does not exist
   *        SUCCESS       if leveled up successfully
   */

    GameStatus nextLevel(const string playerName);

    /**
   * makeStep:  brings a player a step forward
   * @param playerName - The name of the player to step forward.
   *                    type const string
   * return NAME_DOES_NOT_EXIST    if name does not exist
   *        SUCCESS       if steped forward successfully
   */
    GameStatus makeStep(const string playerName);

    /**
   * addLife: add life to player
   * @param playerName - The name of the player to add life to. type const string
   * return NAME_DOES_NOT_EXIST    if name does not exist
   *        SUCCESS                if life added successfully
   */
    GameStatus addLife(const string playerName);

    /**
    * addStrength: add strength to player
    * @param playerName - The name of the player to add strength to.
    *                     type const string
    * @param strengthToAdd - sterngth to add to player. type int
    * return NAME_DOES_NOT_EXIST    if name does not exist
    *        INVALID_PARAM          if strengthToAdd is negative
    *        SUCCESS                if life strength successfully
    */
    GameStatus addStrength(const string playerName, int strengthToAdd);

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
    * @param playerName1 - first player in fight. of type const string
    * @param playerName2 - second player in fight. of type const string
    * return NAME_DOES_NOT_EXIST    if one of the name does not exist
    *        FIGHT_FAILED           if two players cannot fight
    *        SUCCESS                if life strength successfully
    */
    GameStatus fight(const string playerName1, const string playerName2);


    /**
    * removePlayersIf: remove player if object function is true
    */
    template <class FCN>
    bool removePlayersIf(FCN& fcn) {
        bool removed = false;

        // go through all players in array
        for (int i=0; i < maxPlayers; i++) {
            // check if player's weapon is weak
            if(players[i] && fcn(static_cast<const Player&>(*players[i]))) {
                // remove player
                delete players[i];
                players[i] = nullptr;
                removed = true; // update that a player was removed
            }
        }

        // return if players were removed or not
        return removed;
    }



private:
    /**
    * findPlayer: searches for a player in the array
    * @param playerName - the player we are searching for. of type const string
    * return a pointer to the player or null if the player does not exist
    */
    Player* findPlayer(const string& playerName);

    /**
    * removePlayer: removes a player from the array
    * @param playerName - the player we want to remove. of type const string
    */
    void removePlayer(const string& playerName);

    /**
    * sortPlayers: sorts the players in the array by lexicographical order
    */
    void sortPlayers() const;

    /**
    * condensePlayers: moves all of the players to the beginning of the array and
    *                  pushes all of the null pointers to the end of the array.
    */
    bool condensePlayers() const;

};



#endif //HW4_GAME_H
