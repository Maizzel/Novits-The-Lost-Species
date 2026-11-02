#ifndef ENEMYBOT_H
#define ENEMYBOT_H

#include "Trainer.h"

class EnemyBot : public Trainer
{
    public:
        EnemyBot(std::string name);
        virtual ~EnemyBot();

        int chooseAction() override;
};

#endif // ENEMYBOT_H
