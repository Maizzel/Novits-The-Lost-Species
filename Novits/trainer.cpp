#include "Trainer.h"
#include <iostream>

Trainer::Trainer(std::string trainer_name)
    : name(trainer_name), active_novit_index(0), switched_last_turn(false)
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
                  << " (HP: " << team[i].getCurrentHp() << "/" << team[i].getMaxHp() << ")";
        if (!team[i].isAlive())
        {
            std::cout << " [FAINTED]";
        }
        else if (static_cast<int>(i) == active_novit_index)
        {
            std::cout << " [ACTIVE]";
        }
        std::cout << "\n";
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

Novit& Trainer::getActiveNovit()
{
    return team[active_novit_index];
}

int Trainer::getActiveNovitIndex() const
{
    return active_novit_index;
}

void Trainer::setActiveNovitIndex(int index)
{
    if (index >= 0 && index < static_cast<int>(team.size()))
    {
        active_novit_index = index;
    }
}

bool Trainer::hasNovitWithName(const std::string& novit_name) const
{
    for (size_t i = 0; i < team.size(); i++)
    {
        if (team[i].getName() == novit_name)
        {
            return true;
        }
    }
    return false;
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

int Trainer::countAliveNovits() const
{
    int count = 0;
    for (const auto& novit : team)
    {
        if (novit.isAlive())
        {
            count++;
        }
    }
    return count;
}

bool Trainer::getSwitchedLastTurn() const
{
    return switched_last_turn;
}

void Trainer::setSwitchedLastTurn(bool switched)
{
    switched_last_turn = switched;
}
