#include "Trainer.h"
#include <iostream>

Trainer::Trainer(std::string trainer_name)
    : name(trainer_name)
{
}

Trainer::~Trainer()
{
}

std::string Trainer::getName() const
{
    return name;
}

void Trainer::addNovitToTeam(const Novit& novit)
{
    if (team.size() < 4)
    {
        team.push_back(novit);
        std::cout << novit.getName() << " joined " << name << "'s team!\n";
    }
    else
    {
        std::cout << "Team is full! (Max 4 Novits)\n";
    }
}

void Trainer::printTeam() const
{
    std::cout << "=== " << name << "'s Team ===\n";
    for (size_t i = 0; i < team.size(); i++)
    {
        std::cout << "[" << i + 1 << "] " << team[i].getName()
                  << " (HP: " << team[i].getCurrentHp() << "/" << team[i].getMaxHp() << ")\n";
    }
}

Novit& Trainer::getNovit(int index)
{
    if (index >= 0 && index < static_cast<int>(team.size()))
    {
        return team[index];
    }
    return team[0];
}

int Trainer::getTeamSize() const
{
    return team.size();
}

bool Trainer::hasAliveNovits() const
{
    for (const auto& novit : team)
    {
        if (novit.isAlive())
        {
            return true;
        }
    }
    return false;
}
