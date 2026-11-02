#ifndef TRAINER_H
#define TRAINER_H

#include <string>
#include <vector>
#include "Novit.h"

class Trainer
{
    protected:
        std::string name;
        std::vector<Novit> team;

    public:
        Trainer(std::string trainer_name);
        virtual ~Trainer();

        std::string getName() const;
        void addNovitToTeam(const Novit& novit);
        void printTeam() const;

        Novit& getNovit(int index);
        int getTeamSize() const;

        bool hasAliveNovits() const;

        virtual int chooseAction() = 0;
};

#endif // TRAINER_H
