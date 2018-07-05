//
// Created by user on 08-Jun-18.
//
#include <string>
#include <iostream>
#include "Weapon.h"
#ifndef HW4_PLAYER_H
#define HW4_PLAYER_H

using std::ostream;
using std::ofstream;
using std::iostream;
using std::cout;
using std::endl;
using std::string;
class Player {
protected:
    string name;
    Weapon weapon;
    int level;
    int life;
    int strength;
    int tile;

    /**
    * Constructor:   creates a new player
    * @param name - The name of the player. type const string
    * @param weapon - The weapon of the player. type Weapon&
    */
    Player(const string& name, const Weapon& weapon);

public:

   /**
   * Destructor:  destroys the player.
   */
    virtual ~Player() = default;

   /**
   * Copy Constructor: copies a player
   * @param player - player to copy. type const Player&
   */
    Player(const Player& player);

    /**
    * Opertor =: overloads the operator '=' for type player
    * @param player - player to copy. type const Player&
    */
    Player& operator=(const Player& player);

    /**
    * Opertor >: overloads the operator '>' for type player.
    *               Compares player by name.
    * @param player - player to compare. type const Player&
    * return: true - first player's name is earlier in the ABC than the
    *                 second player
    *         false - first player's name is not earlier in the ABC than the
    *                 second player
    */
    bool operator>(const Player& player) const;

    /**
    * Opertor <: overloads the operator '<' for type player.
    *               Compares player by name.
    * @param player - player to compare. type const Player&
    * return: true - first player's name is later in the ABC than the
    *                 second player
    *         false - first player's name is not later in the ABC than the
    *                 second player
    */
    bool operator<(const Player& player);

    /**
    * Operator <<: overloading printing operator for printing a player
    *               output format: {player name: Denis, weapon: <weapon>}}
    */
    friend ostream& operator<<(ostream& os, const Player& player); // printing operator

    /**
    * isPlayer: checks if the player has a certain name
    * @param playerName - name to check. type const string
    * return: true - the player's name is equal to playerName
    *         false - the player's name is not equal to playerName
    */
    bool isPlayer(const string playerName) const;

    /**
    * nextLevel: bring player one level up
    */
    void nextLevel();

    /**
    * makeStep: bring player one step forward
    */
    virtual void makeStep();

    /**
    * addLife: add life to player
    */
    virtual void addLife();

    /**
    * addStrength: add strength to player
    * @param strengthToAdd - the amount of strength to add to the player.
    *                        Of type int.
    */
    void addStrength(int strengthToAdd);

    /**
   * isAlive: checks if the player has any life, strength left or is not level 0
   * return: true - the player's life,strength and level is not 0
   *         false - the player's life,strength and level is 0
   */
    bool isAlive() const;

    /**
    * weaponIsWeak: checks if the player's weapon hit value is under certain
    *               value.
    * @param weaponMinStrength - the minimum value a weapon hit value can be.
    *                              Of type int.
    * return: true - the player's weapon hit value is under the
    *                  minimum strength.
    *         false - the player's weapon hit value is equal or above the
    *                  minimum strength.
    */
    bool weaponIsWeak(int weaponMinStrength) const;

    /**
   * fight: checks if two players can fight if the they can updates their
   *       info accordingly.
   * @param player - player to fight with. of type Player&
   * return: true - the players can fight(they are in the same spot and
   *                have weapons of different hit value).
   *         false - the players can't fight(they are not in the same spot or
   *                have weapons of same hit value).
   */
    bool fight(Player& player);

protected:
    /**
   * canAttack: checks whether our player can attack some other player.
   * a protected function.
   * @param player - the player that we check whether our player can attack.
   */
    virtual bool canAttack(Player const& player) const;
    /**
    * distance: calculates the tile difference between two players.
    * @param player1 - one player.
    * @param player2 - another player.
    */
    static int distance(Player const& player1, Player const& player2);
private:
    /**
   * losePoints: reduces strength, level or life for player.
   *             if target is negative after reduction, make it 0.
   * A private function.
   * @param points - the amount of points lost. type int
   * @param target - which target is losing points. type Target (enum)
   */
    void losePoints(int points, int target);
};


#endif //HW4_PLAYER_H

