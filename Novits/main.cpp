#include <iostream>
#include <ctime>
#include <cstdlib>
#include "NovitDatabase.h"
#include "Player.h"
#include "EnemyBot.h"

using namespace std;

int main()
{
    srand(time(NULL));

    cout << "--- Novits: Inheritance & AI Test ---\n\n";

    Trainer* f1 = new Player("Maciej");
    Trainer* f2 = new EnemyBot("Ash (AI)");

    cout << "Drafting teams...\n";
    f1->addNovitToTeam(NovitDatabase::getNovitById(1));
    f2->addNovitToTeam(NovitDatabase::getNovitById(12));

    cout << "\nTesting Polymorphic chooseAction():\n";

    int playerAction = f1->chooseAction();
    cout << f1->getName() << " chose skill index: " << playerAction << "\n\n";

    int botAction = f2->chooseAction();
    cout << f2->getName() << " chose skill index: " << botAction << "\n";

    delete f1;
    delete f2;

    return 0;
}
