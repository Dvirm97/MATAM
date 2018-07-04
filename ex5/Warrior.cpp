#include "Warrior.h"
#include "mtm_exceptions.h"


Warrior::Warrior(string const& name, Weapon const& weapon, bool rider) :
        Player(name, weapon), mounted(rider)
{
    if (weapon.getTarget() == LEVEL) {
        throw mtm::IllegalWeapon();
    }
}
/*
Warrior::~Warrior() {
    delete[] name;  // delete name
}
*/

void Warrior::makeStep() {
    mounted ? tile+=5 : tile++;
}