#include "skill.h"

Skill::Skill()
    :skill_name("Unknown"), type(SkillType::None), element(Element::None),
     base_power(10), accuracy(100)
{
}

Skill::Skill(std::string name, SkillType typ, Element elem, int base, int acc)
    :skill_name(name), type(typ), element(elem),
     base_power(base), accuracy(acc)
{
}

Skill::~Skill()
{
}

std::string Skill::getName() const
{
    return skill_name;
}

SkillType Skill::getType() const
{
    return type;
}

Element Skill::getElement() const
{
    return element;
}

int Skill::getBasePower() const
{
    return base_power;
}

int Skill::getAccuracy() const
{
    return accuracy;
}
