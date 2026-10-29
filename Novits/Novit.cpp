#include "Novit.h"

Novit::Novit()
    : novit_name("Unknown"), max_hp(100), current_hp(100),
      elemental_attack(6), physical_attack(7), speed(40)
{

}

Novit::Novit(std::string name, int max_hp, int elem_atk, int phys_atk, int speed)
    : novit_name(name), max_hp(max_hp), current_hp(max_hp),
       elemental_attack(elem_atk), physical_attack(phys_atk), speed(speed)
{

}

std::string Novit::getName() const
{
    return novit_name;
}

int Novit::getMaxHp() const
{
    return max_hp;
}

int Novit::getCurrentHp() const
{
    return current_hp;
}

int Novit::getElementalAttack() const
{
    return elemental_attack;
}

int Novit::getPhysicalAttack() const
{
    return physical_attack;
}

int Novit::getSpeed() const
{
    return speed;
}

Novit::~Novit()
{
    //dtor
}
