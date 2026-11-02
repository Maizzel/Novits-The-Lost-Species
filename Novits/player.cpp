#include "Player.h"
#include <iostream>

Player::Player(std::string name) : Trainer(name)
{
}

Player::~Player()
{
}

int Player::chooseAction()
{
    int choice;
    std::cout << name << ", choose your skill (1-4): ";
    std::cin >> choice;

    if (choice < 1 || choice > 4)
    {
        return 0;
    }

    return choice - 1;
}
