#ifndef SKILL_H
#define SKILL_H
#include <string>
#include "Novit.h"

enum class SkillType
{
    None,
    PhysicalAttack,
    ElementalAttack,
    FlatHeal,
    PercentHeal,
    Shield,
    Stun,
};

class Skill
{
    private:
        std::string skill_name;
        SkillType type;
        Element element;
        int base_power;
        int accuracy;

    public:
        Skill();
        Skill(std::string name, SkillType type, Element elem, int power, int acc);
        std::string getName() const;
        SkillType getType() const;
        Element getElement() const;
        int getBasePower() const;
        int getAccuracy() const;

        ~Skill();
};

#endif // SKILL_H
