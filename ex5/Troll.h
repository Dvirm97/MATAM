#ifndef HW5_TROLL_H
#define HW5_TROLL_H

#include "Player.h"
#include <string>
using std::string;

class Troll : public Player {
    int maxLife;
public:
    Troll(string const& name, Weapon const& weapon, int maxLife);
    //~Troll() = default;
    void makeStep() override;
    void addLife() override;
};


#endif //HW5_TROLL_H
