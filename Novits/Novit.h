#ifndef NOVIT_H
#define NOVIT_H
#include <string>

class Novit
{
    private:
        std::string novit_name;
        int max_hp;
        int current_hp;
        int elemental_attack;
        int physical_attack;
        int speed;

    public:
        Novit();
        Novit(std::string name, int max_hp, int elem_atk, int phys_atk, int speed);
        std::string getName() const;
        int getMaxHp() const;
        int getCurrentHp() const;
        int getElementalAttack() const;
        int getPhysicalAttack() const;
        int getSpeed() const;
        virtual ~Novit();


};

#endif // NOVIT_H
