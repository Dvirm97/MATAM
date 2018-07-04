#ifndef HW5_WIZARD_H
#define HW5_WIZARD_H

#include "Player.h"
#include <string>
using std::string;

class Wizard : public Player {
    const int range;
public:
    Wizard(string const& name, Weapon const& weapon, int range); //explicit?
    //~Wizard() = default;
private:
    bool canAttack(const Player& player) const override;
};




#endif //HW5_WIZARD_H
