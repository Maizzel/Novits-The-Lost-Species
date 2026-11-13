#include "Player.h"
#include <iostream>

Player::Player(std::string name) : Trainer(name)
{
}

Player::~Player()
{
}

static std::string elemToText(Element elem)
{
    if (elem == Element::Fire)      return "Fire";
    if (elem == Element::Water)     return "Water";
    if (elem == Element::Nature)    return "Nature";
    if (elem == Element::Earth)     return "Earth";
    if (elem == Element::Wind)      return "Wind";
    if (elem == Element::Lightning) return "Lightning";
    return "None";
}

static std::string skillDetailsToText(const Skill& s)
{
    SkillType t = s.getType();
    std::string pwr = std::to_string(s.getBasePower());
    std::string acc = std::to_string(s.getAccuracy()) + "%";

    if (t == SkillType::PhysicalAttack)
        return "Physical Attack | Power: " + pwr + " | Acc: " + acc;
    if (t == SkillType::ElementalAttack)
        return "Elemental (" + elemToText(s.getElement()) + ") | Power: " + pwr + " | Acc: " + acc;
    if (t == SkillType::FlatHeal)
        return "Flat Heal: +" + pwr + " HP | Acc: " + acc;
    if (t == SkillType::PercentHeal)
        return "Percent Heal: +" + pwr + "% HP | Acc: " + acc;
    if (t == SkillType::Shield)
        return "Shield: +" + pwr + " | Acc: " + acc;
    if (t == SkillType::Stun)
        return "Stun (2 turns) | Acc: " + acc;

    return "Unknown";
}

int Player::chooseAction()
{
    Novit& active_novit = getActiveNovit();
    const std::vector<Skill>& skills = active_novit.getSkills();

    std::cout << "\n--- Your Team ---\n";
    for (size_t i = 0; i < team.size(); ++i)
    {
        std::cout << "[" << i + 1 << "] " << team[i].getName()
                  << " (" << elemToText(team[i].getElement()) << " | HP: "
                  << team[i].getCurrentHp() << "/" << team[i].getMaxHp() << ")";

        if (!team[i].isAlive())
            std::cout << " [FAINTED]";
        else if (static_cast<int>(i) == active_novit_index)
            std::cout << " [ACTIVE]";

        std::cout << "\n";
    }

    std::cout << "\n--- " << active_novit.getName() << "'s Actions ---\n";
    for (size_t i = 0; i < skills.size(); ++i)
    {
        std::cout << "[" << i + 1 << "] " << skills[i].getName()
                  << " (" << skillDetailsToText(skills[i]) << ")";

        if (static_cast<int>(i) == active_novit.getLastUsedSkillIndex())
        {
            std::cout << " [LOCKED - Used last turn!]";
        }
        std::cout << "\n";
    }

    std::cout << "[5] Switch Novit";
    if (switched_last_turn)
    {
        std::cout << " [LOCKED - Switched last turn!]";
    }
    else if (countAliveNovits() <= 1)
    {
        std::cout << " [LOCKED - No other alive Novits!]";
    }
    std::cout << "\n[ff] Surrender (Forfeit match)\n";

    int choice = 0;
    while (true)
    {
        try
        {
            std::cout << name << ", choose your action (1-5 or ff): ";
            std::cin >> choice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::string textInput;
                std::cin >> textInput;
                std::cin.ignore(1000, '\n');

                if (textInput == "ff" || textInput == "FF")
                {
                    return -2;
                }

                throw std::invalid_argument("Input must be a number (1-5) or 'ff'!");
            }

            if (choice < 1 || choice > 5)
            {
                throw std::out_of_range("Action number must be between 1 and 5!");
            }

            if (choice == 5)
            {
                if (switched_last_turn)
                {
                    throw std::logic_error("Anti-spam rule! You cannot switch Novits twice in a row!");
                }
                if (countAliveNovits() <= 1)
                {
                    throw std::logic_error("You have no other alive Novits to switch into!");
                }
                return 4;
            }

            int skill_idx = choice - 1;
            if (skill_idx == active_novit.getLastUsedSkillIndex())
            {
                throw std::logic_error("Anti-spam rule! You cannot use the same skill twice in a row!");
            }

            return skill_idx;
        }
        catch (const std::exception& e)
        {
            std::cout << ">> [ERROR] " << e.what() << "\n";
        }
    }
}
