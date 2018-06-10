//
// Created by user on 08-Jun-18.
//

#include "Player.h"

Player::Player(const char* name, const Weapon& weapon)//, const Weapon& weapon)
{
    this->name = new char[strlen(name)]; //should I not enter size?
    strcpy(this->name, name);
    this->weapon = new Weapon(weapon); //hope this is okay
    this->level = 1;
    this->life = 1;
    this->strength = 1;
    this->tile = 0;
}
/*
Player::~Player() {
    delete[] name;
    delete weapon;
}
 */
ostream& operator<<(ostream& os, const Player& player){
    string str = string("{player name: ") + player.name + ", weapon: ";
    return os << str << *(player.weapon) << "}";
}
void Player::nextLevel() {
    this->level++;
}
bool Player::isPlayer(const char* playerName) const {
    return (strcmp(playerName, this->name) == 0);
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
    return (this->weapon->getValue() < weaponMinStrength);
}
bool Player::operator>(const Player& player) {
    return (strcmp(this->name, player.name) > 0);

}
bool Player::operator<(const Player& player) {
    return (strcmp(this->name, player.name) < 0);
}
bool Player::fight(Player& player) {
    //things
    if (this->tile != player.tile
        || *(this->weapon) == *(player.weapon))
        return false;
    int target; //or maybe TARGET (enum)?
    int points;
    if (*(this->weapon) > *(player.weapon)) {
        target = this->weapon->getTarget();
        points = this->weapon->getHitStrength();
        player.losePoints(points, target);
    }
    else {
        target = player.weapon->getTarget();
        points = player.weapon->getHitStrength();
        this->losePoints(points, target); //really?
    }
    return true;
}
void Player::losePoints(int points, int target) {
    if (target == LEVEL) { //0 == LEVEL
        if (level - points < 0)
            level = 0;
        else
            level -= points;
        return;
    }
    if (target == STRENGTH) { //1 == STRENGTH
        if (strength - points < 0)
            strength = 0;
        else
            strength -= points;
        return;
    }
    if (target == LIFE) { //2 == LIFE
        if (life - points < 0)
            life = 0;
        else
            life -= points;
        return;
    }
}
