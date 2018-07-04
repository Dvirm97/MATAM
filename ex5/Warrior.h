#ifndef HW5_WARRIOR_H
#define HW5_WARRIOR_H

#include "Player.h"
#include <string>
using std::string;

class Warrior : public Player {
    bool mounted;

public:
    /**
    * Constructor:   creates a new warrior
    * @param name - The name of the warrior. type string
    * @param weapon - The weapon of the warrior. type Weapon&
    */
    Warrior(string const& name, Weapon const& weapon, bool rider); //explicit?
    //~Warrior() = default;

    void makeStep() override;
};


#endif //HW5_WARRIOR_H
