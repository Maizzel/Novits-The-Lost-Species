#include "EnemyBot.h"
#include <cstdlib>

EnemyBot::EnemyBot(std::string name) : Trainer(name)
{
}

EnemyBot::~EnemyBot()
{
}

int EnemyBot::chooseAction()
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

    int random_choice;
    bool valid_skill = false;

    while (!valid_skill)
    {
        random_choice = std::rand() % 4;
        SkillType chosen_type = active_novit.getSkills()[random_choice].getType();

        bool is_heal = (chosen_type == SkillType::FlatHeal || chosen_type == SkillType::PercentHeal);
        bool has_max_hp = (active_novit.getCurrentHp() == active_novit.getMaxHp());

        if (is_heal && has_max_hp)
        {
            continue;
        }

        valid_skill = true;
    }

    return random_choice;
}
