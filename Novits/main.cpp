#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include "NovitDatabase.h"
#include "Player.h"
#include "EnemyBot.h"

using namespace std;

string Space(string text)
{
    while (text.length() < 36)
    {
        text += " ";
    }
    return text;
}

string getHpBar(int current, int max)
{
    int totalBars = 10;
    int filled = (current * totalBars) / max;
    if (current > 0 && filled == 0)
    {
        filled = 1;
    }

    string bar = "[";
    for (int i = 0; i < totalBars; i++)
    {
        if (i < filled)
            bar += "#";
        else
            bar += ".";
    }
    bar += "]";
    return bar;
}

string elementToString(Element elem)
{
    if (elem == Element::Fire)      return "Fire";
    if (elem == Element::Water)     return "Water";
    if (elem == Element::Nature)    return "Nature";
    if (elem == Element::Earth)     return "Earth";
    if (elem == Element::Wind)      return "Wind";
    if (elem == Element::Lightning) return "Lightning";
    return "None";
}

void renderBattleScreen(int turn, const string& pName, const Novit& pNovit,
                        const string& bName, const Novit& bNovit,
                        const vector<string>& lastTurnLogs)
{
    system("cls");

    cout << "========================================================================\n";
    cout << "                   NOVITS: THE LOST SPECIES - TURN " << turn << "\n";
    cout << "========================================================================\n\n";

    cout << Space("[PLAYER] " + pName) << "|   " << "[BOT] " + bName << "\n";
    cout << "------------------------------------+-----------------------------------\n";

    string pNovitTitle = "Novit: " + pNovit.getName() + " (" + elementToString(pNovit.getElement()) + ")";
    string bNovitTitle = "Novit: " + bNovit.getName() + " (" + elementToString(bNovit.getElement()) + ")";
    cout << Space(pNovitTitle) << "|   " << bNovitTitle << "\n";

    string pHp = "HP: " + getHpBar(pNovit.getCurrentHp(), pNovit.getMaxHp()) + " "
                 + to_string(pNovit.getCurrentHp()) + "/" + to_string(pNovit.getMaxHp());
    string bHp = "HP: " + getHpBar(bNovit.getCurrentHp(), bNovit.getMaxHp()) + " "
                 + to_string(bNovit.getCurrentHp()) + "/" + to_string(bNovit.getMaxHp());
    cout << Space(pHp) << "|   " << bHp << "\n";

    string pStats = "PHYS: " + to_string(pNovit.getPhysicalAttack())
                  + " | ELEM: " + to_string(pNovit.getElementalAttack())
                  + " | SPD: " + to_string(pNovit.getSpeed());
    string bStats = "PHYS: " + to_string(bNovit.getPhysicalAttack())
                  + " | ELEM: " + to_string(bNovit.getElementalAttack())
                  + " | SPD: " + to_string(bNovit.getSpeed());
    cout << Space(pStats) << "|   " << bStats << "\n";

    string pStatus = "Status: ";
    if (pNovit.getShield() > 0) pStatus += "[SHIELD: " + to_string(pNovit.getShield()) + "] ";
    if (pNovit.getIsStunned())  pStatus += "[STUNNED] ";
    if (pNovit.getShield() == 0 && !pNovit.getIsStunned()) pStatus += "OK";

    string bStatus = "Status: ";
    if (bNovit.getShield() > 0) bStatus += "[SHIELD: " + to_string(bNovit.getShield()) + "] ";
    if (bNovit.getIsStunned())  bStatus += "[STUNNED] ";
    if (bNovit.getShield() == 0 && !bNovit.getIsStunned()) bStatus += "OK";

    cout << Space(pStatus) << "|   " << bStatus << "\n";
    cout << "========================================================================\n";

    cout << " [ LAST TURN ]\n";
    for (size_t i = 0; i < lastTurnLogs.size(); i++)
    {
        cout << "  " << lastTurnLogs[i] << "\n";
    }
    cout << "========================================================================\n";
}

double getElementMultiplier(Element attackElem, Element defenderElem)
{
    if (attackElem == Element::None || defenderElem == Element::None)
    {
        return 1.0;
    }

    if ((attackElem == Element::Fire      && defenderElem == Element::Nature)    ||
        (attackElem == Element::Nature    && defenderElem == Element::Water)     ||
        (attackElem == Element::Water     && defenderElem == Element::Fire)      ||
        (attackElem == Element::Earth     && defenderElem == Element::Lightning) ||
        (attackElem == Element::Lightning && defenderElem == Element::Wind)      ||
        (attackElem == Element::Wind      && defenderElem == Element::Earth))
    {
        return 1.5;
    }

    if (attackElem == defenderElem ||
        (attackElem == Element::Fire      && defenderElem == Element::Water)     ||
        (attackElem == Element::Nature    && defenderElem == Element::Fire)      ||
        (attackElem == Element::Water     && defenderElem == Element::Nature)    ||
        (attackElem == Element::Lightning && defenderElem == Element::Earth)     ||
        (attackElem == Element::Wind      && defenderElem == Element::Lightning) ||
        (attackElem == Element::Earth     && defenderElem == Element::Wind))
    {
        return 0.5;
    }

    return 1.0;
}

void executeTurn(Novit& attacker, Novit& defender, int skillIndex, vector<string>& lastTurnLogs)
{
    if (attacker.getIsStunned())
    {
        lastTurnLogs.push_back(">> " + attacker.getName() + " is STUNNED and skips the turn!");
        attacker.setStunned(false);
        return;
    }

    const Skill& skill = attacker.getSkills()[skillIndex];
    attacker.setLastUsedSkillIndex(skillIndex);

    string msg = ">> " + attacker.getName() + " uses [" + skill.getName() + "]! ";

    int roll = (rand() % 100) + 1;
    if (roll > skill.getAccuracy())
    {
        msg += "MISSED! (Rolled " + to_string(roll) + " vs " + to_string(skill.getAccuracy()) + "%)";
        lastTurnLogs.push_back(msg);
        return;
    }

    SkillType type = skill.getType();

    if (type == SkillType::PhysicalAttack)
    {
        int dmg = skill.getBasePower() + attacker.getPhysicalAttack();
        defender.takeDamage(dmg);
        msg += "Deals " + to_string(dmg) + " physical damage to " + defender.getName() + "!";
        lastTurnLogs.push_back(msg);
    }
    else if (type == SkillType::ElementalAttack)
    {
        int baseDmg = skill.getBasePower() + attacker.getElementalAttack();
        double multiplier = getElementMultiplier(skill.getElement(), defender.getElement());

        int dmg = static_cast<int>(baseDmg * multiplier);

        defender.takeDamage(dmg);
        msg += "Deals " + to_string(dmg) + " elemental damage to " + defender.getName() + "!";

        if (multiplier > 1.0)
        {
            msg += " [SUPER EFFECTIVE! x1.5]";
        }
        else if (multiplier < 1.0)
        {
            msg += " [NOT VERY EFFECTIVE... x0.5]";
        }

        lastTurnLogs.push_back(msg);
    }
    else if (type == SkillType::FlatHeal)
    {
        attacker.healFlat(skill.getBasePower());
        msg += "Healed for " + to_string(skill.getBasePower()) + " HP!";
        lastTurnLogs.push_back(msg);
    }
    else if (type == SkillType::PercentHeal)
    {
        attacker.healPercent(skill.getBasePower());
        msg += "Restored " + to_string(skill.getBasePower()) + "% of Max HP!";
        lastTurnLogs.push_back(msg);
    }
    else if (type == SkillType::Shield)
    {
        attacker.setShield(skill.getBasePower());
        msg += "Gained a SHIELD of " + to_string(skill.getBasePower()) + " points!";
        lastTurnLogs.push_back(msg);
    }
    else if (type == SkillType::Stun)
    {
        defender.setStunned(true);
        msg += defender.getName() + " is now STUNNED for the next turn!";
        lastTurnLogs.push_back(msg);
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

    Trainer* player = new Player("Maciej");
    Trainer* bot = new EnemyBot("Ash (AI)");

    player->addNovitToTeam(NovitDatabase::getNovitById(1));
    bot->addNovitToTeam(NovitDatabase::getNovitById(9));

    Novit& pNovit = player->getNovit(0);
    Novit& bNovit = bot->getNovit(0);

    vector<string> lastTurnLogs;
    lastTurnLogs.push_back("Battle started! Choose your first skill below.");

    int turn = 1;
    while (pNovit.isAlive() && bNovit.isAlive())
    {
        renderBattleScreen(turn, player->getName(), pNovit, bot->getName(), bNovit, lastTurnLogs);

        int playerSkillIdx = player->chooseAction();
        int botSkillIdx = bot->chooseAction();

        lastTurnLogs.clear();

        if (pNovit < bNovit)
        {
            executeTurn(bNovit, pNovit, botSkillIdx, lastTurnLogs);
            if (pNovit.isAlive())
            {
                executeTurn(pNovit, bNovit, playerSkillIdx, lastTurnLogs);
            }
        }
        else
        {
            executeTurn(pNovit, bNovit, playerSkillIdx, lastTurnLogs);
            if (bNovit.isAlive())
            {
                executeTurn(bNovit, pNovit, botSkillIdx, lastTurnLogs);
            }
        }

        turn++;
    }

    renderBattleScreen(turn - 1, player->getName(), pNovit, bot->getName(), bNovit, lastTurnLogs);

    cout << "\n========================================================================\n";
    if (pNovit.isAlive())
    {
        cout << "   VICTORY! " << player->getName() << " wins the battle!\n";
    }
    else
    {
        cout << "   DEFEAT! " << bot->getName() << " wins the battle!\n";
    }
    cout << "   Final State -> " << pNovit << "  VS  " << bNovit << "\n";
    cout << "========================================================================\n";

    delete player;
    delete bot;

    return 0;
}
