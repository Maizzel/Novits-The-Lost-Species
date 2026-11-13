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

    if ((attackElem == Element::Fire      && defenderElem == Element::Water)     ||
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

void waitForEnter(string message)
{
    cout << "\n" << message;
    cin.ignore(1000, '\n');
    cin.get();
}

void draftTeams(Trainer* player, Trainer* opponent, bool isPvP)
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
            cout << player->getName() << ", pick Novit #" << (player->getTeamSize() + 1) << " (enter ID 1-18): ";
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
            cout << ">> Added " << chosen.getName() << " to " << player->getName() << "'s team!\n";
        }
        catch (const exception& e)
        {
            cout << ">> [ERROR] " << e.what() << "\n";
        }
    }

    if (isPvP)
    {
        cout << "\n------------------------------------------------------------------------\n";
        while (opponent->getTeamSize() < 4)
        {
            try
            {
                cout << opponent->getName() << ", pick Novit #" << (opponent->getTeamSize() + 1) << " (enter ID 1-18): ";
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
                if (opponent->hasNovitWithName(chosen.getName()))
                {
                    throw logic_error("You already have " + chosen.getName() + " in your team! Pick a different Novit.");
                }

                opponent->addNovitToTeam(chosen);
                cout << ">> Added " << chosen.getName() << " to " << opponent->getName() << "'s team!\n";
            }
            catch (const exception& e)
            {
                cout << ">> [ERROR] " << e.what() << "\n";
            }
        }
    }
    else
    {
        while (opponent->getTeamSize() < 4)
        {
            int randomId = (rand() % 18) + 1;
            Novit botPick = NovitDatabase::getNovitById(randomId);
            if (!opponent->hasNovitWithName(botPick.getName()))
            {
                opponent->addNovitToTeam(botPick);
            }
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

void renderBattleScreen(int turn, Trainer* player, Trainer* opponent, const vector<string>& lastTurnLogs)
{
    system("cls");

    Novit& pNovit = player->getActiveNovit();
    Novit& bNovit = opponent->getActiveNovit();

    cout << "========================================================================\n";
    cout << "                 NOVITS: THE LOST SPECIES (4v4) - TURN " << turn << "\n";
    cout << "========================================================================\n\n";

    string pHeader = "[P1] " + player->getName() + " (Alive: " + to_string(player->countAliveNovits()) + "/4)";
    string bHeader = "[P2] " + opponent->getName() + " (Alive: " + to_string(opponent->countAliveNovits()) + "/4)";
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
    if (pNovit.getStunDuration() > 0)  pStatus += "[STUNNED (" + to_string(pNovit.getStunDuration()) + " turns)] ";
    if (pNovit.getShield() == 0 && pNovit.getStunDuration() == 0) pStatus += "OK";

    string bStatus = "Status: ";
    if (bNovit.getShield() > 0) bStatus += "[SHIELD: " + to_string(bNovit.getShield()) + "] ";
    if (bNovit.getStunDuration() > 0)  bStatus += "[STUNNED (" + to_string(bNovit.getStunDuration()) + " turns)] ";
    if (bNovit.getShield() == 0 && bNovit.getStunDuration() == 0) bStatus += "OK";

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
    if (attacker.getStunDuration() > 0)
    {
        lastTurnLogs.push_back(">> " + attacker.getName() + " is STUNNED and skips the turn!");
        attacker.applyStun(0);
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
        defender.applyStun(2);
        msg += defender.getName() + " is now STUNNED for 2 turns!";
        lastTurnLogs.push_back(msg);
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

    system("cls");
    cout << "========================================================================\n";
    cout << "                      NOVITS: THE LOST SPECIES                          \n";
    cout << "========================================================================\n\n";
    cout << "[1] Player vs Bot\n";
    cout << "[2] Player vs Player (1v1 on one screen)\n\n";

    int mode = 0;
    while (true)
    {
        try
        {
            cout << "Choose mode (1-2): ";
            cin >> mode;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                throw invalid_argument("Input must be a number, not letters!");
            }
            if (mode != 1 && mode != 2)
            {
                throw out_of_range("Choice must be 1 or 2!");
            }
            break;
        }
        catch (const exception& e)
        {
            cout << ">> [ERROR] " << e.what() << "\n";
        }
    }

    bool isPvP = (mode == 2);

    string name1;
    cout << "Enter Player 1 nickname: ";
    cin >> name1;
    Trainer* player = new Player(name1);

    Trainer* bot = nullptr;
    if (isPvP)
    {
        string name2;
        cout << "Enter Player 2 nickname: ";
        cin >> name2;
        bot = new Player(name2);
    }
    else
    {
        bot = new EnemyBot("Ash (AI)");
    }

    draftTeams(player, bot, isPvP);

    vector<string> lastTurnLogs;

    bool isPlayerTurn = !(player->getActiveNovit() < bot->getActiveNovit());
    bool switchedJustHappened = false;

    lastTurnLogs.push_back("Battle started! " + player->getActiveNovit().getName()
                           + " vs " + bot->getActiveNovit().getName() + "!");

    int turn = 1;
    while (player->hasAliveNovits() && bot->hasAliveNovits())
    {
        Trainer* current = isPlayerTurn ? player : bot;
        Trainer* enemy   = isPlayerTurn ? bot : player;

        if (current->getActiveNovit().getStunDuration() > 0)
        {
            renderBattleScreen(turn, player, bot, lastTurnLogs);
            waitForEnter(">> " + current->getActiveNovit().getName() + " is STUNNED! Press ENTER to skip turn...");

            lastTurnLogs.clear();
            lastTurnLogs.push_back(">> " + current->getActiveNovit().getName() + " was STUNNED and skipped the turn!");
            current->getActiveNovit().reduceStun();

            if (switchedJustHappened)
            {
                switchedJustHappened = false;
                isPlayerTurn = !(player->getActiveNovit() < bot->getActiveNovit());
            }
            else
            {
                isPlayerTurn = !isPlayerTurn;
            }
            turn++;
            continue;
        }

        int action = -1;
        int switchTargetIdx = -1;

        if (isPlayerTurn || isPvP)
        {
            while (true)
            {
                renderBattleScreen(turn, player, bot, lastTurnLogs);
                action = current->chooseAction();

                if (action == 4)
                {
                    switchTargetIdx = chooseSwitchTarget(current, true);
                    if (switchTargetIdx == -1)
                    {
                        continue;
                    }
                }
                break;
            }
        }
        else
        {
            renderBattleScreen(turn, player, bot, lastTurnLogs);
            waitForEnter(">> Now it's " + current->getName() + "'s turn! Press ENTER to see opponent's move...");
            action = current->chooseAction();
        }

        lastTurnLogs.clear();

        if (action == -2)
        {
            for (int i = 0; i < current->getTeamSize(); i++)
            {
                current->getNovit(i).setShield(0);
                current->getNovit(i).takeDamage(9999);
            }
            lastTurnLogs.push_back(">> [SURRENDER] " + current->getName() + " forfeited the match!");
            turn++;
            break;
        }

        if (action == 4)
        {
            string oldName = current->getActiveNovit().getName();
            current->getActiveNovit().applyStun(0);

            current->moveNovitToTop(switchTargetIdx);
            current->setSwitchedLastTurn(true);

            lastTurnLogs.push_back(">> " + current->getName() + " switched out " + oldName
                                   + " (moved to bottom) and sent in " + current->getActiveNovit().getName() + "!");

            isPlayerTurn = !isPlayerTurn;
            switchedJustHappened = true;
        }
        else
        {
            current->setSwitchedLastTurn(false);
            executeTurn(current->getActiveNovit(), enemy->getActiveNovit(), action, lastTurnLogs);

            if (!enemy->getActiveNovit().isAlive())
            {
                lastTurnLogs.push_back(">> [KO!] " + enemy->getName() + "'s " + enemy->getActiveNovit().getName() + " fainted!");
                switchedJustHappened = false;

                if (enemy->hasAliveNovits())
                {
                    for (int i = 0; i < enemy->getTeamSize(); i++)
                    {
                        if (enemy->getNovit(i).isAlive())
                        {
                            enemy->moveNovitToTop(i);
                            enemy->setSwitchedLastTurn(false);
                            lastTurnLogs.push_back(">> " + enemy->getName() + " automatically sends out " + enemy->getActiveNovit().getName() + "!");
                            break;
                        }
                    }

                    isPlayerTurn = !(player->getActiveNovit() < bot->getActiveNovit());
                }
            }
            else
            {
                if (switchedJustHappened)
                {
                    switchedJustHappened = false;
                    bool fasterIsPlayer = !(player->getActiveNovit() < bot->getActiveNovit());

                    if (fasterIsPlayer == isPlayerTurn)
                    {
                        lastTurnLogs.push_back(">> [SPEED!] " + current->getActiveNovit().getName() + " is faster and gets a 2nd turn in a row!");
                    }
                    isPlayerTurn = fasterIsPlayer;
                }
                else
                {
                    isPlayerTurn = !isPlayerTurn;
                }
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
        cout << "   VICTORY! " << bot->getName() << " wins the battle!\n";
    }
    cout << "   Final State -> " << player->getActiveNovit() << "  VS  " << bot->getActiveNovit() << "\n";
    cout << "========================================================================\n";

    delete player;
    delete bot;

    return 0;
}
