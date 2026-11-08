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

void draftTeams(Trainer* player, Trainer* bot)
{
    system("cls");
    cout << "========================================================================\n";
    cout << "                  NOVITS: THE LOST SPECIES - 4v4 DRAFT                  \n";
    cout << "========================================================================\n\n";

    vector<Novit> allNovits = NovitDatabase::getAllNovits();
    for (size_t i = 0; i < allNovits.size(); i++)
    {
        string entry = "[" + to_string(i + 1) + "] " + allNovits[i].getName()
                     + " (" + elementToString(allNovits[i].getElement()) + ")";
        cout << Space(entry);
        if ((i + 1) % 2 == 0) cout << "\n";
    }
    cout << "\n========================================================================\n";

    while (player->getTeamSize() < 4)
    {
        try
        {
            cout << "Pick Novit #" << (player->getTeamSize() + 1) << " (enter ID 1-18): ";
            int id;
            cin >> id;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                throw invalid_argument("Input must be a number, not letters!");
            }

            if (id < 1 || id > 18)
            {
                throw out_of_range("ID must be between 1 and 18!");
            }

            Novit chosen = NovitDatabase::getNovitById(id);
            if (player->hasNovitWithName(chosen.getName()))
            {
                throw logic_error("You already have " + chosen.getName() + " in your team! Pick a different Novit.");
            }

            player->addNovitToTeam(chosen);
            cout << ">> Added " << chosen.getName() << " to your team!\n";
        }
        catch (const exception& e)
        {
            cout << ">> [ERROR] " << e.what() << "\n";
        }
    }

    while (bot->getTeamSize() < 4)
    {
        int randomId = (rand() % 18) + 1;
        Novit botPick = NovitDatabase::getNovitById(randomId);
        if (!bot->hasNovitWithName(botPick.getName()))
        {
            bot->addNovitToTeam(botPick);
        }
    }
}

int chooseSwitchTarget(Trainer* player, bool allowCancel)
{
    cout << "\n";
    player->printTeam();
    if (allowCancel)
    {
        cout << "[5] Cancel (Go back to actions)\n";
    }

    int choice = 0;
    while (true)
    {
        try
        {
            if (allowCancel)
                cout << "Choose Novit (1-4) or 5 to cancel: ";
            else
                cout << "Choose Novit to send into battle (1-4): ";

            cin >> choice;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                throw invalid_argument("Input must be a number, not letters!");
            }

            if (allowCancel && choice == 5)
            {
                return -1;
            }

            int maxOption = allowCancel ? 5 : 4;
            if (choice < 1 || choice > maxOption)
            {
                throw out_of_range("Choice out of range!");
            }

            int idx = choice - 1;
            if (idx == player->getActiveNovitIndex())
            {
                throw logic_error("That Novit is already in battle!");
            }
            if (!player->getNovit(idx).isAlive())
            {
                throw logic_error("That Novit has fainted and cannot fight!");
            }

            return idx;
        }
        catch (const exception& e)
        {
            cout << ">> [ERROR] " << e.what() << "\n";
        }
    }
}

void renderBattleScreen(int turn, Trainer* player, Trainer* bot, const vector<string>& lastTurnLogs)
{
    system("cls");

    Novit& pNovit = player->getActiveNovit();
    Novit& bNovit = bot->getActiveNovit();

    cout << "========================================================================\n";
    cout << "                 NOVITS: THE LOST SPECIES (4v4) - TURN " << turn << "\n";
    cout << "========================================================================\n\n";

    string pHeader = "[PLAYER] " + player->getName() + " (Alive: " + to_string(player->countAliveNovits()) + "/4)";
    string bHeader = "[BOT] " + bot->getName() + " (Alive: " + to_string(bot->countAliveNovits()) + "/4)";
    cout << Space(pHeader) << "|   " << bHeader << "\n";
    cout << "------------------------------------+-----------------------------------\n";

    string pTitle = "Novit: " + pNovit.getName() + " (" + elementToString(pNovit.getElement()) + ")";
    string bTitle = "Novit: " + bNovit.getName() + " (" + elementToString(bNovit.getElement()) + ")";
    cout << Space(pTitle) << "|   " << bTitle << "\n";

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

        if (multiplier > 1.0)      msg += " [SUPER EFFECTIVE! x1.5]";
        else if (multiplier < 1.0) msg += " [NOT VERY EFFECTIVE... x0.5]";

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

    draftTeams(player, bot);

    vector<string> lastTurnLogs;
    lastTurnLogs.push_back("Battle started! " + player->getActiveNovit().getName()
                           + " vs " + bot->getActiveNovit().getName() + "!");

    int turn = 1;
    while (player->hasAliveNovits() && bot->hasAliveNovits())
    {
        int playerAction = -1;
        int switchTargetIdx = -1;

        while (true)
        {
            renderBattleScreen(turn, player, bot, lastTurnLogs);
            playerAction = player->chooseAction();

            if (playerAction == 4)
            {
                switchTargetIdx = chooseSwitchTarget(player, true);
                if (switchTargetIdx == -1)
                {
                    continue;
                }
            }
            break;
        }

        int botSkillIdx = bot->chooseAction();
        lastTurnLogs.clear();

        if (playerAction == 4)
        {
            string oldName = player->getActiveNovit().getName();

            player->getActiveNovit().setStunned(false);
            player->setActiveNovitIndex(switchTargetIdx);
            player->setSwitchedLastTurn(true);

            lastTurnLogs.push_back(">> " + player->getName() + " switched out " + oldName
                                   + " and sent in " + player->getActiveNovit().getName() + "!");

            executeTurn(bot->getActiveNovit(), player->getActiveNovit(), botSkillIdx, lastTurnLogs);
        }
        else
        {
            player->setSwitchedLastTurn(false);

            Novit& pNovit = player->getActiveNovit();
            Novit& bNovit = bot->getActiveNovit();

            if (pNovit < bNovit)
            {
                executeTurn(bNovit, pNovit, botSkillIdx, lastTurnLogs);
                if (pNovit.isAlive())
                {
                    executeTurn(pNovit, bNovit, playerAction, lastTurnLogs);
                }
            }
            else
            {
                executeTurn(pNovit, bNovit, playerAction, lastTurnLogs);
                if (bNovit.isAlive())
                {
                    executeTurn(bNovit, pNovit, botSkillIdx, lastTurnLogs);
                }
            }
        }

        if (!bot->getActiveNovit().isAlive())
        {
            lastTurnLogs.push_back(">> [KO!] Bot's " + bot->getActiveNovit().getName() + " fainted!");
            if (bot->hasAliveNovits())
            {
                for (int i = 0; i < bot->getTeamSize(); i++)
                {
                    if (bot->getNovit(i).isAlive())
                    {
                        bot->setActiveNovitIndex(i);
                        lastTurnLogs.push_back(">> Bot sends out " + bot->getActiveNovit().getName() + "!");
                        break;
                    }
                }
            }
        }

        if (!player->getActiveNovit().isAlive())
        {
            lastTurnLogs.push_back(">> [KO!] Your " + player->getActiveNovit().getName() + " fainted!");
            if (player->hasAliveNovits())
            {
                renderBattleScreen(turn, player, bot, lastTurnLogs);
                cout << "\n>> Your Novit fainted! You must send out another one:\n";
                int nextIdx = chooseSwitchTarget(player, false);
                player->setActiveNovitIndex(nextIdx);
                player->setSwitchedLastTurn(false);
                lastTurnLogs.push_back(">> You sent out " + player->getActiveNovit().getName() + "!");
            }
        }

        turn++;
    }

    renderBattleScreen(turn - 1, player, bot, lastTurnLogs);

    cout << "\n========================================================================\n";
    if (player->hasAliveNovits())
    {
        cout << "   VICTORY! " << player->getName() << " wins the battle!\n";
    }
    else
    {
        cout << "   DEFEAT! " << bot->getName() << " wins the battle!\n";
    }
    cout << "   Final State -> " << player->getActiveNovit() << "  VS  " << bot->getActiveNovit() << "\n";
    cout << "========================================================================\n";

    delete player;
    delete bot;

    return 0;
}
