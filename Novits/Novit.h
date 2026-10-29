#ifndef NOVIT_H
#define NOVIT_H
#include <string>

enum class Element
{
    None,
    Fire,
    Water,
    Nature,
    Earth,
    Wind,
    Lightning
};

class Novit
{
    private:
        std::string novit_name;
        Element element;
        int max_hp;
        int current_hp;
        int elemental_attack;
        int physical_attack;
        int speed;

    public:
        Novit();
        Novit(std::string name, Element elem, int max_hp, int elem_atk, int phys_atk, int speed);
        std::string getName() const;
        virtual ~Novit();

        Element getElement() const;
        int getMaxHp() const;
        int getCurrentHp() const;
        int getElementalAttack() const;
        int getPhysicalAttack() const;
        int getSpeed() const;

        bool isAlive() const;
        void takeDamage(int damage);

};

#endif // NOVIT_H
