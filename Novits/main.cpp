#include <iostream>
#include "NovitDatabase.h"

using namespace std;

int main()
{
    cout << "--- Novits: Combat Mechanics & Operator Test ---\n\n";

    Novit slowTank = NovitDatabase::getNovitById(10);
    Novit fastStriker = NovitDatabase::getNovitById(15);

    cout << "Combatants:\n";
    cout << "Fighter 1: " << slowTank << "\n";
    cout << "Fighter 2: " << fastStriker << "\n\n";

    cout << "Speed check for first strike:\n";
    if (slowTank < fastStriker)
    {
        cout << ">> " << fastStriker.getName() << " is faster and strikes first!\n\n";
    }
    else
    {
        cout << ">> " << slowTank.getName() << " strikes first!\n\n";
    }

    cout << "Shield test on " << slowTank.getName() << ":\n";
    slowTank.setShield(30);
    cout << slowTank << "\n";

    cout << "Incoming attack with 20 damage:\n";
    slowTank.takeDamage(20);
    cout << slowTank << "\n\n";

    cout << "Incoming attack with 25 damage:\n";
    slowTank.takeDamage(25);
    cout << slowTank << "\n";

    return 0;
}
