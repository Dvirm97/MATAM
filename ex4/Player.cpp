/**
 * class Player
 */

#include "Player.h"

// Constructor
Player::Player(const char* name, const Weapon& weapon):
   weapon(weapon), level(1), life(1), strength(1), tile(0) {
    // copy name
   this->name = new char[strlen(name)+1];
   strcpy(this->name, name);
}
// Destructor
Player::~Player() {
    delete[] name;  // delete name
}
// Copy Constructor
Player::Player(const Player& player):
        weapon(player.weapon), level(player.level), life(player.life),
        strength(player.strength), tile(player.tile) {
    // copy name
    this->name = new char[strlen(player.name)+1];
    strcpy(this->name, player.name);
}
// operator '=' overloading
Player& Player::operator=(const Player& player)
{
    // check if already equal
    if (this == &player) return *this;

    // delete previouse content
    delete[] name;

    // copy new content
    this->name = new char[strlen(player.name)+1];
    strcpy(this->name, player.name);
    this->weapon = player.weapon;
    this->level = player.level;
    this->life = player.life;
    this->strength = player.strength;
    this->tile = player.tile;

    // return player with new info
    return *this;
}
// printing operator overlaoding
ostream& operator<<(ostream& os, const Player& player){
    return os << "{player name: " << player.name << ", weapon: " <<
              player.weapon << "}";
}
void Player::nextLevel() {
    this->level++;
}
bool Player::isPlayer(const char* playerName) const {
    return strcmp(playerName, name) == 0; // compare names
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
    return (this->level > 0 && this->strength > 0 && this->life > 0);
}
bool Player::weaponIsWeak(int weaponMinStrength) const {
    return (weapon.getValue() < weaponMinStrength);
}
bool Player::operator>(const Player& player) {
    return strcmp(name, player.name) > 0; // compare strings
}
bool Player::operator<(const Player& player) {
    return strcmp(name, player.name) < 0; // compare strings
}
bool Player::fight(Player& player) {
    // check if can fight
    if (this->tile != player.tile || this->weapon == player.weapon) {
        return false;
    }
    // define variables
    int target, points;

    // update info for losing player
    if (this->weapon > player.weapon) {
        target = this->weapon.getTarget();
        points = this->weapon.getHitStrength();
        player.losePoints(points, target);
    }
    else {
        target = player.weapon.getTarget();
        points = player.weapon.getHitStrength();
        this->losePoints(points, target);
    }

    return true;
}
void Player::losePoints(int points, int target) {
    switch (target) {
        case LEVEL:
            level -= points;
            if (level < 0) {
                level = 0;
            }
            break;
        case STRENGTH:
            strength -= points;
            if (strength < 0) {
                strength = 0;
            }
            break;
        case LIFE:
            life -= points;
            if (life < 0) {
                life = 0;
            }
            break;
        default:
            return;
    }
}
