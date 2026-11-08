#include "Player.h"
#include <iostream>

Player::Player(std::string name) : Trainer(name)
{
}

Player::~Player()
{
}

int Player::chooseAction()
{
    int active_idx = 0;
    for (size_t i = 0; i < team.size(); ++i)
    {
        if (team[i].isAlive())
        {
            active_idx = i;
            break;
        }
    }

    Novit& active_novit = team[active_idx];
    const std::vector<Skill>& skills = active_novit.getSkills();

    std::cout << "\n--- " << active_novit.getName() << "'s Skills ---\n";
    for (size_t i = 0; i < skills.size(); ++i)
    {
        std::cout << "[" << i + 1 << "] " << skills[i].getName()
                  << " (Power: " << skills[i].getBasePower()
                  << ", Acc: " << skills[i].getAccuracy() << "%)";

        if (static_cast<int>(i) == active_novit.getLastUsedSkillIndex())
        {
            std::cout << " [LOCKED - Used last turn!]";
        }
        std::cout << "\n";
    }

    int choice = 0;
    while (true)
    {
        try
        {
            std::cout << name << ", choose your skill (1-4): ";
            std::cin >> choice;

            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                throw std::invalid_argument("Input must be a number, not letters!");
            }

            if (choice < 1 || choice > 4)
            {
                throw std::out_of_range("Skill number must be between 1 and 4!");
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
