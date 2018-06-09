//
// Created by user on 08-Jun-18.
//
#include <cstring>
#ifndef HW4_PLAYER_H
#define HW4_PLAYER_H


class Player {
    char *name;
    int level;
    int life;
    int strength;
    Weapon weapon;
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
    bool fight(Player& player);
    void losePoints(int points, int target);
};
bool operator>(const Player& player1, const Player& player2);
bool operator<(const Player& player1, const Player& player2);


    Player::Player(const char* name, Weapon& weapon)//, const Weapon& weapon)
    {
        this->name = new char[strlen(name)]; //should I not enter size?
        strcpy(this->name, name);
        this->Weapon = new Weapon;
        this->weapon = weapon;
        this->level = 1;
        this->life = 1;
        this->strength = 1;
        this->tile = 0;
    }
Player::~Player() {
        delete[] this->name;
        delete this->weapon;
    }
void Player::nextLevel() {
        this->level++;
    }
bool Player::isPlayer(const char* playerName) const {
    return ((bool)strcmp(playerName, this->name)); //hope this is right
}
void Player::makeStep() {
    this->tile++;
}
void Player::addLife() {
    this->life++;
}
void Player::addStrength(int strengthToAdd) {
    this->strength += strengthToAdd;
}
bool Player::isAlive() const {
    return (this->level > 0
            && this->strength > 0
            && this->life > 0);

}
bool Player::weaponIsWeak(int weaponMinStrength) const {
    return (this->weapon < weaponMinStrength);
}
bool Player::operator>(const Player& player1, const Player& player2) {
    return (strcmp(player1->name, player2->name) > 0);

}
bool Player::operator<(const Player& player1, const Player& player2) {
    return (strcmp(player1->name, player2->name) < 0);
}
bool Player::fight(Player& player) {
    //things
    if (this->tile != player.tile
        || this->weapon == player.weapon)
        return false;
    int target; //or maybe TARGET (enum)?
    int points;
    if (this->weapon > player.weapon) {
        target = this->weapon.getTarget();
        points = this->weapon.getHitStrength();
        player.losePoints(points, target);
    }
    else {
        target = player.weapon.getTarget();
        points = player.weapon.getHitStrength();
        this->losePoints(points, target); //really?
    }
    return true;
}
void Player::losePoints(int points, int target) {
    if (target == 0) { //0 == LEVEL
        if (level - points < 0)
            level = 0;
        else
            level -= points;
        return;
    }
    if (target == 1) { //1 == STRENGTH
        if (strength - points < 0)
            strength = 0;
        else
            strength -= points;
        return;
    }
    if (target == 2) { //2 == LIFE
        if (life - points < 0)
            life = 0;
        else
            life -= points;
        return;
    }
}

#endif //HW4_PLAYER_H
