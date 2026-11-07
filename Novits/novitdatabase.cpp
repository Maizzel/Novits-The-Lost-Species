#include "NovitDatabase.h"

std::vector<Novit> NovitDatabase::getAllNovits()
{
    std::vector<Novit> pool;
    pool.reserve(18);

    // 1. FIRE - ID: 1, 2, 3
    {
        // ID 1: Ranwey
        Novit n("Ranwey", Element::Fire, 115, 14, 10, 48);
        n.addSkill(Skill("Edur", SkillType::PhysicalAttack, Element::None, 15, 100));
        n.addSkill(Skill("Firye", SkillType::ElementalAttack, Element::Fire, 22, 95));
        n.addSkill(Skill("YeYe", SkillType::FlatHeal, Element::None, 25, 100));
        n.addSkill(Skill("4th Dimension", SkillType::Shield, Element::None, 30, 100));
        pool.push_back(n);
    }
    {
        // ID 2: El Flame
        Novit n("El Flame", Element::Fire, 95, 15, 11, 60);
        n.addSkill(Skill("Sicko", SkillType::PhysicalAttack, Element::None, 16, 100));
        n.addSkill(Skill("Lit", SkillType::ElementalAttack, Element::Fire, 22, 95));
        n.addSkill(Skill("Heal - You Should Try It", SkillType::PercentHeal, Element::None, 25, 100));
        n.addSkill(Skill("Bird in Trap", SkillType::Stun, Element::None, 0, 75));
        pool.push_back(n);
    }
    {
        // ID 3: Sentow
        Novit n("Sentow", Element::Fire, 105, 13, 15, 52);
        n.addSkill(Skill("Knife", SkillType::PhysicalAttack, Element::None, 18, 100));
        n.addSkill(Skill("Pow", SkillType::ElementalAttack, Element::Fire, 24, 90));
        n.addSkill(Skill("Take It Easy", SkillType::PercentHeal, Element::None, 25, 100));
        n.addSkill(Skill("Hustle", SkillType::Shield, Element::None, 25, 100));
        pool.push_back(n);
    }

    // 2. WATER - ID: 4, 5, 6
    {
        // ID 4: MinM
        Novit n("MinM", Element::Water, 100, 14, 14, 58);
        n.addSkill(Skill("Berzerk", SkillType::PhysicalAttack, Element::None, 17, 100));
        n.addSkill(Skill("Kamikaze", SkillType::ElementalAttack, Element::Water, 23, 95));
        n.addSkill(Skill("Won't Collapse", SkillType::FlatHeal, Element::None, 25, 100));
        n.addSkill(Skill("Discombobulated", SkillType::Stun, Element::None, 0, 75));
        pool.push_back(n);
    }
    {
        // ID 5: Focean
        Novit n("Focean", Element::Water, 110, 15, 9, 46);
        n.addSkill(Skill("Solo", SkillType::PhysicalAttack, Element::None, 15, 100));
        n.addSkill(Skill("Good Swim", SkillType::ElementalAttack, Element::Water, 21, 95));
        n.addSkill(Skill("Nights", SkillType::PercentHeal, Element::None, 25, 100));
        n.addSkill(Skill("Black + Yellow", SkillType::Stun, Element::None, 0, 75));
        pool.push_back(n);
    }
    {
        // ID 6: J-Sea
        Novit n("J-Sea", Element::Water, 115, 16, 12, 44);
        n.addSkill(Skill("Blue-Print-Punch", SkillType::PhysicalAttack, Element::None, 16, 100));
        n.addSkill(Skill("Empire State of Tide", SkillType::ElementalAttack, Element::Water, 20, 95));
        n.addSkill(Skill("99 Puddles", SkillType::ElementalAttack, Element::Water, 32, 85));
        n.addSkill(Skill("Hard Knock Reef", SkillType::Shield, Element::None, 30, 100));
        pool.push_back(n);
    }

    // 3. NATURE - ID: 7, 8, 9
    {
        // ID 7: Skinniest J
        Novit n("Skinniest J", Element::Nature, 95, 13, 14, 62);
        n.addSkill(Skill("Beat (It)", SkillType::PhysicalAttack, Element::None, 16, 100));
        n.addSkill(Skill("People's Nature", SkillType::ElementalAttack, Element::Nature, 21, 95));
        n.addSkill(Skill("Be Something", SkillType::FlatHeal, Element::None, 25, 100));
        n.addSkill(Skill("Dirty", SkillType::Stun, Element::None, 0, 75));
        pool.push_back(n);
    }
    {
        // ID 8: Dr. Tree
        Novit n("Dr. Tree", Element::Nature, 125, 12, 11, 40);
        n.addSkill(Skill("Need a doctor?", SkillType::PhysicalAttack, Element::None, 15, 100));
        n.addSkill(Skill("Throwing these nuts", SkillType::ElementalAttack, Element::Nature, 20, 95));
        n.addSkill(Skill("One bar", SkillType::PercentHeal, Element::None, 25, 100));
        n.addSkill(Skill("Still T.R.E.E", SkillType::Shield, Element::None, 35, 100));
        pool.push_back(n);
    }
    {
        // ID 9: OutGrass
        Novit n("OutGrass", Element::Nature, 120, 14, 12, 45);
        n.addSkill(Skill("So Fresh So Green", SkillType::PhysicalAttack, Element::None, 16, 100));
        n.addSkill(Skill("Ms. Oakson", SkillType::ElementalAttack, Element::Nature, 22, 95));
        n.addSkill(Skill("Roses Thornwall", SkillType::Shield, Element::None, 30, 100));
        n.addSkill(Skill("Hay Ya!", SkillType::Stun, Element::None, 0, 75));
        pool.push_back(n);
    }

    // 4. EARTH - ID: 10, 11, 12
    {
        // ID 10: Killaquen
        Novit n("Killaquen", Element::Earth, 125, 12, 13, 38);
        n.addSkill(Skill("Bite the Dust", SkillType::PhysicalAttack, Element::None, 17, 100));
        n.addSkill(Skill("Rock you", SkillType::ElementalAttack, Element::Earth, 20, 95));
        n.addSkill(Skill("Good time", SkillType::FlatHeal, Element::None, 25, 100));
        n.addSkill(Skill("Don't stop me", SkillType::Shield, Element::None, 30, 100));
        pool.push_back(n);
    }
    {
        // ID 11: Fast Rocker
        Novit n("Fast Rocker", Element::Earth, 110, 13, 15, 55);
        n.addSkill(Skill("Smoke away", SkillType::PhysicalAttack, Element::None, 17, 100));
        n.addSkill(Skill("Sandguy", SkillType::ElementalAttack, Element::Earth, 22, 95));
        n.addSkill(Skill("Phoenix Armor", SkillType::Shield, Element::None, 30, 100));
        n.addSkill(Skill("Be Dumb", SkillType::Stun, Element::None, 0, 75));
        pool.push_back(n);
    }
    {
        // ID 12: Pink Stone
        Novit n("Pink Stone", Element::Earth, 130, 16, 10, 35);
        n.addSkill(Skill("Hey, you!", SkillType::PhysicalAttack, Element::None, 15, 100));
        n.addSkill(Skill("Dark Side of the Stone", SkillType::ElementalAttack, Element::Earth, 20, 95));
        n.addSkill(Skill("Another Brick", SkillType::ElementalAttack, Element::Earth, 32, 85));
        n.addSkill(Skill("Crazy Quartz", SkillType::Shield, Element::None, 30, 100));
        pool.push_back(n);
    }

    // 5. WIND - ID: 13, 14, 15
    {
        // ID 13: Big T
        Novit n("Big T", Element::Wind, 105, 14, 12, 56);
        n.addSkill(Skill("Cherry Bombing", SkillType::PhysicalAttack, Element::None, 16, 100));
        n.addSkill(Skill("Hotter Wind Blows", SkillType::ElementalAttack, Element::Wind, 21, 95));
        n.addSkill(Skill("Yonk", SkillType::FlatHeal, Element::None, 25, 100));
        n.addSkill(Skill("Glitter", SkillType::Shield, Element::None, 28, 100));
        pool.push_back(n);
    }
    {
        // ID 14: Led Zephyr
        Novit n("Led Zephyr", Element::Wind, 100, 15, 12, 60);
        n.addSkill(Skill("Rumble", SkillType::PhysicalAttack, Element::None, 16, 100));
        n.addSkill(Skill("Whole Lotta Wind", SkillType::ElementalAttack, Element::Wind, 22, 95));
        n.addSkill(Skill("Airway Shield", SkillType::Shield, Element::None, 28, 100));
        n.addSkill(Skill("Kashmir Draft", SkillType::Stun, Element::None, 0, 75));
        pool.push_back(n);
    }
    {
        // ID 15: Don Tornado
        Novit n("Don Tornado", Element::Wind, 90, 17, 11, 66);
        n.addSkill(Skill("Torn Up", SkillType::PhysicalAttack, Element::None, 15, 100));
        n.addSkill(Skill("After Breeze", SkillType::ElementalAttack, Element::Wind, 20, 95));
        n.addSkill(Skill("Windonade", SkillType::ElementalAttack, Element::Wind, 32, 85));
        n.addSkill(Skill("No Air-dea", SkillType::Stun, Element::None, 0, 70));
        pool.push_back(n);
    }

    // 6. LIGHTNING - ID: 16, 17, 18

    {
        // ID 16: Eisidisi
        Novit n("Eisidisi", Element::Lightning, 90, 16, 16, 65);
        n.addSkill(Skill("Alternate Current", SkillType::ElementalAttack, Element::Lightning, 18, 100));
        n.addSkill(Skill("Direct Current", SkillType::ElementalAttack, Element::Lightning, 25, 90));
        n.addSkill(Skill("Black in Back", SkillType::PhysicalAttack, Element::None, 22, 95));
        n.addSkill(Skill("Road to Hell", SkillType::Stun, Element::None, 0, 70));
        pool.push_back(n);
    }
    {
        // ID 17: RadioLeg
        Novit n("RadioLeg", Element::Lightning, 100, 15, 10, 54);
        n.addSkill(Skill("Weirdo", SkillType::PhysicalAttack, Element::None, 15, 100));
        n.addSkill(Skill("Step Down Transformer", SkillType::ElementalAttack, Element::Lightning, 22, 95));
        n.addSkill(Skill("High Voltage & Dry", SkillType::PercentHeal, Element::None, 25, 100));
        n.addSkill(Skill("Static Police", SkillType::Stun, Element::None, 0, 75));
        pool.push_back(n);
    }
    {
        // ID 18: Daft Spark
        Novit n("Daft Spark", Element::Lightning, 110, 16, 11, 50);
        n.addSkill(Skill("Robo-Shock", SkillType::PhysicalAttack, Element::None, 16, 100));
        n.addSkill(Skill("Harder Better Faster Volter", SkillType::ElementalAttack, Element::Lightning, 20, 95));
        n.addSkill(Skill("One More Spark", SkillType::ElementalAttack, Element::Lightning, 32, 85));
        n.addSkill(Skill("Around the Coil", SkillType::Shield, Element::None, 30, 100));
        pool.push_back(n);
    }

    return pool;
}

Novit NovitDatabase::getNovitById(int id)
{
    std::vector<Novit> pool = getAllNovits();
    if (id >= 1 && id <= static_cast<int>(pool.size()))
    {
        return pool[id - 1];
    }
    return pool[0];
}
