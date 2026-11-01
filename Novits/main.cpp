#include <iostream>
#include "NovitDatabase.h"
#include "Player.h"

using namespace std;

int main()
{
    cout << "--- Novits: The Lost Species ---\n\n";

    Player player1("Maciej");

    player1.addNovitToTeam(NovitDatabase::getNovitById(1));
    player1.addNovitToTeam(NovitDatabase::getNovitById(6));
    player1.addNovitToTeam(NovitDatabase::getNovitById(9));
    player1.addNovitToTeam(NovitDatabase::getNovitById(18));

    player1.addNovitToTeam(NovitDatabase::getNovitById(12));

    cout << endl;

    player1.printTeam();

    return 0;
}
