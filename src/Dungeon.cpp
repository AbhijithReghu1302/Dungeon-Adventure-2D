#include <iostream>
#include <cstdlib>
#include "../include/Dungeon.h"

using namespace std;

void Dungeon::explore(Player& player)
{
    int encounter = rand() % 3;

    cout << "\nYou enter a mysterious dungeon room...\n\n";

    switch (encounter)
    {
        case 0:
            cout << "A dangerous enemy appears!\n";
            cout << "Combat will be available in the next update.\n";
            break;

        case 1:
        {
            int treasure = 10 + rand() % 41;

            cout << "You discovered a treasure chest!\n";
            cout << "You found " << treasure << " gold!\n";

            player.addGold(treasure);
            break;
        }

        case 2:
            cout << "The room is empty and silent...\n";
            cout << "You continue your journey.\n";
            break;
    }
}