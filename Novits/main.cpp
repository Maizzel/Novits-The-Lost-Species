#include <iostream>
#include <vector>
#include "NovitDatabase.h"

using namespace std;

int main()
{
    cout << "--- Novits: The Lost Species ---\n";

    vector<Novit> allNovits = NovitDatabase::getAllNovits();

    cout << "Novit Pool (Loaded: " << allNovits.size() << "/18):\n" << endl;

    for (int i = 0; i < allNovits.size(); i++)
    {
        cout << "[" << i + 1 << "] " << allNovits[i].getName()
             << " | HP: " << allNovits[i].getMaxHp()
             << " | Speed: " << allNovits[i].getSpeed() << "\n";

        for (int j = 0; j < allNovits[i].getSkills().size(); j++)
        {
            cout << "   - " << allNovits[i].getSkills()[j].getName()
                 << " (Power: " << allNovits[i].getSkills()[j].getBasePower() << ")\n";
        }
        cout << "----------------------------------------\n";
    }

    return 0;
}
