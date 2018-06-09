//
// Created by user on 08-Jun-18.
//
#include <cstring>
#include "Weapon.h"
#ifndef HW4_PLAYER_H
#define HW4_PLAYER_H


class Player {
    char *name;
    int level;
    int life;
    int strength;
    Weapon* weapon; //not sure
    int tile;

public:
    Player(const char* name, const Weapon& weapon);
    ~Player();
    void nextLevel();
    bool isPlayer(const char* playerName) const;
    void makeStep();
    void addLife();
    void addStrength(int strengthToAdd);
    bool isAlive() const;
    bool weaponIsWeak(int weaponMinStrength) const;
    bool operator>(const Player& player);
    bool operator<(const Player& player);
    bool fight(Player& player);
    void losePoints(int points, int target);
};


#endif //HW4_PLAYER_H
