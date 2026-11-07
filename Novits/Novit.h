#ifndef NOVIT_H
#define NOVIT_H
#include <string>
#include <vector>
#include "skill.h"

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
        std::vector<Skill> skills;
        int shield;
        bool is_stunned;
        int last_used_skill_index;

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

        void addSkill(const Skill& skill);
        const std::vector<Skill>& getSkills() const;

        void healFlat(int amount);
        void healPercent(int percent);
        void setShield(int amount);
        int getShield() const;
        void setStunned(bool stunned);
        bool getIsStunned() const;

        bool operator<(const Novit& other) const;

        int getLastUsedSkillIndex() const;
        void setLastUsedSkillIndex(int index);
};

std::ostream& operator<<(std::ostream& os, const Novit& novit);

#endif // NOVIT_H
