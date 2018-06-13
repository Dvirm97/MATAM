/**
 * class Weapon
 */

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
    /**
    * Constructor:   creates a new weapon
    * @param name - The name of the weapon. type const char*
    * @param target - The target the weapon. an enum value of Target
    * @param hit_strength - The basic amount of strength the weapon hits.
    *                       Of type int.
    */
    Weapon(const char* name, Target target, int hit_strength);

    /**
    * Destructor:  destroys the weapon.
    */
    ~Weapon();

    /**
    * Copy Constructor: copies a weapon
    * @param weapon - weapon to copy. type const Weapon&
    */
    Weapon(const Weapon& weapon);

    /**
    * Opertor =: overloads the operator '=' for type weapon
    * @param weapon - weapon to insert. type const Weapon&
    */
    Weapon& operator=(const Weapon& weapon);

    /**
    * Opertor ==: overloads the operator '==' for type weapon.
    *               Compares weapons by hit value.
    * @param weapon - weapon to compare. type const Weapon&
    * return: true - hit value for both weapons is equal
    *         false - hit value for both weapons is not equal
    */
    bool operator==(const Weapon& weapon) const;

    /**
    * Opertor !=: overloads the operator '!=' for type weapon.
    *               Compares weapons by hit value.
    * @param weapon - weapon to compare. type const Weapon&
    * return: true - hit value for both weapons is not equal
    *         false - hit value for both weapons is equal
    */
    bool operator!=(const Weapon& weapon) const;

    /**
    * Opertor >: overloads the operator '>' for type weapon.
    *               Compares weapons by hit value.
    * @param weapon - weapon to compare. type const Weapon&
    * return: true - hit value for first weapon is bigger than the second weapon
    *         false - hit value for first weapon is not bigger than the second weapon
    */
    bool operator>(const Weapon& weapon) const;

    /**
    * Opertor <: overloads the operator '<' for type weapon.
    *               Compares weapons by hit value.
    * @param weapon - weapon to compare. type const Weapon&
    * return: true - hit value for first weapon is smaller than the second weapon
    *         false - hit value for first weapon is not smaller than the second weapon
    */
    bool operator<(const Weapon& weapon) const;

    /**
    * Operator <<: overloading printing operator for printing a weapon
    *        output format: {weapon name: <name>, weapon value:<hit value>}
    */
    friend ostream& operator<<(ostream& os, const Weapon& weapon);

    /**
    * getTarget: return the target of the weapon
    */
    Target getTarget() const;

    /**
    * getHitStrength: return the strength of the hit of the weapon
    */
    int getHitStrength() const;

    /**
    * getValue: calculates and returns the hit value of the weapon
    *           value = (<target> + 1) * hitStrength
    */
    int getValue() const;
};
#endif //HW4_WEAPON_H
