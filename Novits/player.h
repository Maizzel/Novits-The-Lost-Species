#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Novit.h"

class Player
{
    private:
        std::string player_name;
        std::vector<Novit> team;

    public:
        Player(std::string name);

        std::string getName() const;
        void addNovitToTeam(const Novit& novit);
        void printTeam() const;

        Novit& getNovit(int index);
        int getTeamSize() const;

        bool hasAliveNovits() const;
};

#endif // PLAYER_H
