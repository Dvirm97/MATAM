/**
 * class Player
 */

#include "Player.h"
#include <cstring> //should be <string>
//using std::string;

// Constructor
Player::Player(const string& name, const Weapon& weapon):
   weapon(weapon), level(1), life(1), strength(1), tile(0) {
    // copy name
   this->name = name;
}
/*
// Destructor
Player::~Player() {
    delete[] name;  // delete name
}
*/
//Copy Constructor
Player::Player(const Player& player):
        weapon(player.weapon), level(player.level), life(player.life),
        strength(player.strength), tile(player.tile) {
    // copy name
    this->name = player.name;
}
// operator '=' overloading
Player& Player::operator=(const Player& player)
{
    // check if already equal
    if (this == &player) return *this;

    // copy new content
    this->name = player.name;
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
bool Player::isPlayer(const string playerName) const {
    return (playerName == name); // compare names
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
bool Player::operator>(const Player& player) const {
    return this->name > player.name; // compare strings
}
bool Player::operator<(const Player& player) {
    return this->name < player.name; // compare strings
}
bool Player::fight(Player& player) {
    if (this->canAttack(player)) {
        int target = this->weapon.getTarget();
        int points = this->weapon.getHitStrength();
        player.losePoints(points, target);
        return true;
    }
    if (player.canAttack(*this)) {
        int target = player.weapon.getTarget();
        int points = player.weapon.getHitStrength();
        this->losePoints(points, target);
        return true;
    }
    return false;
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

bool Player::canAttack(Player const& player) const {
    return (this->tile == player.tile
            && this->weapon > player.weapon);
}

int Player::distance(Player const& player1, Player const& player2) {
    int difference = player1.tile - player2.tile;
    return (difference < 0 ? -difference : difference);
}