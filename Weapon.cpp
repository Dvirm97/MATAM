//
// Created by user on 09-Jun-18.
//
#include "Weapon.h"

//using namespace std;

Weapon::Weapon(const char* name, Target target, int hit_strength){
    this->name = new char[strlen(name)];
    strcpy(this->name, name);
    this->target = target;
    this->hitStrength = hit_strength;
}

Target Weapon::getTarget() const {
    return target;
}
int Weapon::getHitStrength() const {
    return hitStrength;
}
/*
Weapon::~Weapon(){
    delete[] name;
}
*/
int Weapon::getValue() const{
    if(target == LEVEL) return 1 * hitStrength;
    else if(target == STRENGTH) return 2 * hitStrength;
    else if(target == LIFE) return 3 * hitStrength;
    return 0;
}
bool Weapon::operator==(const Weapon& weapon) const {
    return getValue() == weapon.getValue();
}
bool Weapon::operator!=(const Weapon& weapon) const {
    return getValue() != weapon.getValue();
}
bool Weapon::operator>(const Weapon& weapon) const {
    return getValue() > weapon.getValue();
}
bool Weapon::operator<(const Weapon& weapon) const {
    return getValue() < weapon.getValue();
}

ostream& operator<<(ostream& os, const Weapon& weapon){
    return os << "{weapon name: " << weapon.name << ", weapon value: " <<
              weapon.getValue() << "}";
}

