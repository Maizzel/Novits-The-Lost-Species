#ifndef PLAYER_H
#define PLAYER_H

#include "Trainer.h"

class Player : public Trainer
{
    public:
        Player(std::string name);
        virtual ~Player();

        int chooseAction() override;
};

#endif // PLAYER_H
