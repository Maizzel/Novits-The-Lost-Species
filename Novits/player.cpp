#include "Player.h"
#include <iostream>

Player::Player(std::string name)
    : player_name(name)
{
}

std::string Player::getName() const
{
    return player_name;
}

void Player::addNovitToTeam(const Novit& novit)
{
    if (team.size() < 4)
    {
        team.push_back(novit);
        std::cout << novit.getName() << " joined " << player_name << "'s team!\n";
    }
    else
    {
        std::cout << "Team is full! (Max 4 Novits)\n";
    }
}

void Player::printTeam() const
{
    std::cout << "=== " << player_name << "'s Team ===\n";
    for (int i = 0; i < team.size(); i++)
    {
        std::cout << "[" << i + 1 << "] " << team[i].getName()
                  << " (HP: " << team[i].getCurrentHp() << "/" << team[i].getMaxHp() << ")\n";
    }
}

Novit& Player::getNovit(int index)
{
    if (index >= 0 && index < static_cast<int>(team.size()))
    {
        return team[index];
    }
    return team[0];
}

int Player::getTeamSize() const
{
    return team.size();
}

bool Player::hasAliveNovits() const
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
