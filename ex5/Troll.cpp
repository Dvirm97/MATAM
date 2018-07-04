#include "Troll.h"
#include "mtm_exceptions.h"



Troll::Troll(string const& name, Weapon const& weapon, int maxLife) :
        Player(name, weapon), maxLife(maxLife)
{
    if (maxLife <= 0) {
        throw mtm::InvalidParam();
    }
}
/*
Troll::~Troll() {
    delete[] name;  // delete name
}
*/

void Troll::makeStep() {
    tile+=2;
    addLife();
}

void Troll::addLife() {
    if (life < maxLife)
        life++;
}

