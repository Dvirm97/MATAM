#include "Wizard.h"
#include "mtm_exceptions.h"

Wizard::Wizard(string const& name, Weapon const& weapon, int range) :
        Player(name, weapon), range(range)
{
    if (range < 0) {
        throw mtm::InvalidParam();
    }
    if (weapon.getTarget() == LIFE) {
        throw mtm::IllegalWeapon();
    }
}
bool Wizard::canAttack(const Player& player) const {
    int dist = distance(*this, player);
    return (dist <= range
            && dist != 0
            && player.weaponIsWeak(this->weapon.getValue()));
}
