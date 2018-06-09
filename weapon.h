#ifndef HW4_WEAPON_H
#define HW4_WEAPON_H
#include <cstring>
#include <iostream>
#include <ostream>

using namespace std;

enum Target{
    LEVEL,
    STRENGTH,
    LIFE
};
class Weapon {
    char* name;
    Target target;
    int hitStrength;

public:
    Weapon(const char* name, Target target, int hit_strength);
    ~Weapon() = default;
    Weapon&operator=(const Weapon&) = default;

    Target getTarget() const;
    int getHitStregnth() const;
    int getValue() const;
    bool operator==(const Weapon& weapon) const;
    bool operator!=(const Weapon& weapon) const;
    bool operator>(const Weapon& weapon) const;
    bool operator<(const Weapon& weapon) const;
    ostream& operator<<(ostream& os, const Weapon& weapon);
};

Weapon::Weapon(const char* name, Target target, int hit_strength){
    this->name = new char[strlen(name)];
    strcpy(this->name, name);
    this->target = target;
    this->hitStrength = hit_strength;
}

Target Weapon::getTarget() const {
    return target;
}
int Weapon::getHitStregnth() const {
    return hitStrength;
}
int Weapon::getValue() const{
    if(target == LEVEL) return 1 * hitStrength;
    if(target == STRENGTH) return 2 * hitStrength;
    if(target == LIFE) return 3 * hitStrength;
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

ostream& operator<<(ostream& os, Weapon& weapon) const {
    string str = string("{weapon name:") + weapon.name + ",weapon value:";
    return os << str << weapon.getValue() << "}";
}

#endif //HW4_WEAPON_H
