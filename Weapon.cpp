/**
 * class Weapon
 */

#include "Weapon.h"

// Constructor
Weapon::Weapon(const char* name, Target target, int hit_strength):
        target(target), hitStrength(hit_strength){
    // copy name
    this->name = new char[strlen(name)+1];
    strcpy(this->name, name);
}
// Destructor
Weapon::~Weapon(){
    delete[] name;  // delete name
}
// Copy Constructor
Weapon::Weapon(const Weapon& weapon):
        target(weapon.target), hitStrength(weapon.hitStrength) {
    // copy name
    this->name = new char[strlen(weapon.name)+1];
    strcpy(this->name, weapon.name);
}
// operator = overloading
Weapon& Weapon::operator=(const Weapon& weapon) {
    // check if already equal
    if (this == &weapon) return *this;

    // delete current fields
    delete[] name;

    // copy new fields
    this->name = new char[strlen(weapon.name)+1];
    strcpy(this->name, weapon.name);
    this->target = weapon.target;
    this->hitStrength = weapon.hitStrength;

    // return new weapon
    return *this;
}
Target Weapon::getTarget() const {
    return target;
}
int Weapon::getHitStrength() const {
    return hitStrength;
}
int Weapon::getValue() const{
    return ((int)target + 1)*hitStrength;
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
// overloading printing operator
ostream& operator<<(ostream& os, const Weapon& weapon){
    return os << "{weapon name: " << weapon.name << ", weapon value:" <<
              weapon.getValue() << "}";
}

