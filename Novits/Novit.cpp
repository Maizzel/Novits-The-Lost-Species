#include <iostream>
#include "Novit.h"

Novit::Novit()
    : novit_name("Unknown"), element(Element::None), max_hp(100), current_hp(100),
      elemental_attack(6), physical_attack(7), speed(40), shield(0), is_stunned(false)
{
}

Novit::Novit(std::string name, Element elem, int max_hp, int elem_atk, int phys_atk, int speed)
    : novit_name(name), element(elem), max_hp(max_hp), current_hp(max_hp),
      elemental_attack(elem_atk), physical_attack(phys_atk), speed(speed), shield(0),
      is_stunned(false)
{
}

Novit::~Novit()
{
}

std::string Novit::getName() const
{
    return novit_name;
}

Element Novit::getElement() const
{
    return element;
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

bool Novit::isAlive() const
{
    return current_hp > 0;
}

void Novit::takeDamage(int damage)
{
    if (shield > 0)
    {
        if (damage <= shield)
        {
            shield -= damage;
            std::cout << novit_name << "'s shield absorbed all " << damage << " damage!\n";
            return;
        }
        else
        {
            damage -= shield;
            std::cout << novit_name << "'s shield broke! Remaining " << damage << " damage hits directly!\n";
            shield = 0;
        }
    }

    current_hp -= damage;
    if (current_hp < 0)
    {
        current_hp = 0;
    }
}

void Novit::healFlat(int amount)
{
    current_hp += amount;
    if (current_hp > max_hp)
    {
        current_hp = max_hp;
    }
}

void Novit::healPercent(int percent)
{
    int amount = (max_hp * percent) / 100;
    healFlat(amount);
}

void Novit::setShield(int amount)
{
    shield = amount;
}

int Novit::getShield() const
{
    return shield;
}

void Novit::setStunned(bool stunned)
{
    is_stunned = stunned;
}

bool Novit::getIsStunned() const
{
    return is_stunned;
}

void Novit::addSkill(const Skill& skill)
{
    if (skills.size() < 4)
    {
        skills.push_back(skill);
    }
}

const std::vector<Skill>& Novit::getSkills() const
{
    return skills;
}

bool Novit::operator<(const Novit& other) const
{
    return this->speed < other.speed;
}

std::ostream& operator<<(std::ostream& os, const Novit& novit)
{
    os << novit.getName() << " [HP: " << novit.getCurrentHp() << "/" << novit.getMaxHp()
       << " | SPD: " << novit.getSpeed() << "]";
    if (novit.getShield() > 0)
    {
        os << " (SHIELD: " << novit.getShield() << ")";
    }
    return os;
}
