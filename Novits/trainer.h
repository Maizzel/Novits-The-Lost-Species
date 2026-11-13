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
        int active_novit_index;
        bool switched_last_turn;

    public:
        Trainer(std::string trainer_name);
        virtual ~Trainer();

        std::string getName() const;
        void addNovitToTeam(const Novit& novit);
        void printTeam() const;

        Novit& getNovit(int index);
        int getTeamSize() const;

        Novit& getActiveNovit();
        int getActiveNovitIndex() const;
        void setActiveNovitIndex(int index);

        void moveNovitToTop(int index);

        bool hasNovitWithName(const std::string& novit_name) const;
        bool hasAliveNovits() const;
        int countAliveNovits() const;

        bool getSwitchedLastTurn() const;
        void setSwitchedLastTurn(bool switched);

        virtual int chooseAction() = 0;
};

#endif // TRAINER_H
