#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "../include/Game.h"

using namespace std;

void Player::showStats() const
{
    cout << "\n========== PLAYER STATS ==========\n";
    cout << "Name: " << name << "\n";
    cout << "Level: " << level << "\n";
    cout << "HP: " << hp << "/" << maxHp << "\n";
    cout << "Attack: " << attack << "\n";
    cout << "Defense: " << defense << "\n";
    cout << "Weapon: " << weapon << "\n";
    cout << "Gold: " << gold << "\n";
    cout << "XP: " << xp << "/" << level * 100 << "\n";
    cout << "Potions: " << potions << "\n";
    cout << "Dungeon Room: " << room << "/5\n";
    cout << "==================================\n";
}

void Player::addXP(int amount)
{
    xp += amount;

    while (xp >= level * 100)
    {
        xp -= level * 100;
        level++;
        maxHp += 20;
        hp = maxHp;
        attack += 5;
        defense += 2;

        cout << "\n*** LEVEL UP! ***\n";
        cout << "You are now level " << level << "!\n";
        cout << "Your health and combat stats increased!\n";
    }
}

Enemy Dungeon::createEnemy(bool boss, int level) const
{
    Enemy e;

    if (boss)
    {
        e.name = "Dungeon Dragon";
        e.hp = 160 + level * 20;
        e.attack = 22 + level * 3;
        e.defense = 8 + level;
        e.xpReward = 200;
        e.goldReward = 200;
        return e;
    }

    int type = rand() % 3;

    if (type == 0)
        e.name = "Goblin";
    else if (type == 1)
        e.name = "Skeleton";
    else
        e.name = "Orc";

    e.hp = 35 + level * 10 + rand() % 16;
    e.attack = 9 + level * 2 + rand() % 5;
    e.defense = 3 + level;
    e.xpReward = 30;
    e.goldReward = 15 + rand() % 21;

    return e;
}

int Game::readChoice(int min, int max)
{
    int choice;

    while (true)
    {
        cout << "Enter choice: ";

        if (cin >> choice && choice >= min && choice <= max)
            return choice;

        cout << "Invalid input! Enter a number from "
             << min << " to " << max << ".\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void Game::pause()
{
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Game::start()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    cout << "========================================\n";
    cout << "          DUNGEON ADVENTURE             \n";
    cout << "========================================\n";

    showMainMenu();
}

void Game::showMainMenu()
{
    while (true)
    {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. New Game\n";
        cout << "2. Load Game\n";
        cout << "3. Exit\n";

        int choice = readChoice(1, 3);

        if (choice == 1)
            startNewGame();
        else if (choice == 2)
        {
            if (loadGame())
                showAdventureMenu();
            else
                cout << "No saved game found or save file is invalid.\n";
        }
        else
        {
            cout << "Thanks for playing Dungeon Adventure!\n";
            return;
        }
    }
}

void Game::startNewGame()
{
    player = Player();
    gameOver = false;

    cout << "\nEnter your character name: ";
    cin >> ws;
    getline(cin, player.name);

    if (player.name.empty())
        player.name = "Adventurer";

    playerCreated = true;

    cout << "\nWelcome, " << player.name << "!\n";
    cout << "Your adventure begins now.\n";

    showAdventureMenu();
}

void Game::showAdventureMenu()
{
    if (!playerCreated)
        return;

    while (!gameOver)
    {
        cout << "\n========== ADVENTURE MENU ==========\n";
        cout << "Player: " << player.name
             << " | HP: " << player.hp << "/" << player.maxHp
             << " | Gold: " << player.gold << "\n\n";

        cout << "1. Explore Dungeon\n";
        cout << "2. View Player Stats\n";
        cout << "3. Inventory\n";
        cout << "4. Use Health Potion\n";
        cout << "5. Save Game\n";
        cout << "6. Return to Main Menu\n";

        int choice = readChoice(1, 6);

        switch (choice)
        {
            case 1:
                exploreDungeon();
                break;

            case 2:
                player.showStats();
                pause();
                break;

            case 3:
                showInventory();
                pause();
                break;

            case 4:
                usePotion();
                pause();
                break;

            case 5:
                saveGame();
                pause();
                break;

            case 6:
                cout << "Returning to main menu...\n";
                return;
        }
    }
}

void Game::exploreDungeon()
{
    if (player.room > 5)
    {
        cout << "The dungeon has already been completed!\n";
        return;
    }

    cout << "\nYou enter Dungeon Room " << player.room << "...\n";

    if (player.room == 5)
    {
        cout << "THE FINAL BOSS IS WAITING FOR YOU!\n";
        battle(true);
        return;
    }

    int event = rand() % 3;

    if (event == 0)
    {
        cout << "An enemy approaches!\n";
        battle(false);
    }
    else if (event == 1)
    {
        int treasure = 15 + rand() % 36;
        player.gold += treasure;

        cout << "You discover a treasure chest!\n";
        cout << "You collected " << treasure << " gold.\n";

        if (rand() % 3 == 0)
        {
            player.potions++;
            cout << "You also found a health potion!\n";
        }
    }
    else
    {
        cout << "The room is empty. You continue cautiously.\n";
    }

    if (!gameOver)
    {
        player.room++;
        cout << "You progress to Room " << player.room << ".\n";
    }

    pause();
}

void Game::battle(bool boss)
{
    Enemy enemy = dungeon.createEnemy(boss, player.level);

    cout << "\n========================================\n";
    cout << "             BATTLE BEGINS              \n";
    cout << "========================================\n";
    cout << "Enemy: " << enemy.name << "\n";
    cout << "Enemy HP: " << enemy.hp << "\n";

    while (player.hp > 0 && enemy.hp > 0)
    {
        cout << "\n" << player.name
             << " HP: " << player.hp << "/" << player.maxHp << "\n";

        cout << enemy.name << " HP: " << enemy.hp << "\n";
        cout << "1. Attack\n";
        cout << "2. Use Potion\n";
        cout << "3. Run Away\n";

        int choice = readChoice(1, 3);

        if (choice == 1)
        {
            int damage = max(1, player.attack
                                - enemy.defense
                                + rand() % 6);

            enemy.hp = max(0, enemy.hp - damage);

            cout << "You dealt " << damage << " damage!\n";
        }
        else if (choice == 2)
        {
            if (player.potions <= 0)
            {
                cout << "You have no health potions!\n";
                continue;
            }

            player.potions--;
            int healing = min(40, player.maxHp - player.hp);
            player.hp += healing;

            cout << "You recovered " << healing << " HP!\n";
        }
        else
        {
            if (boss)
            {
                cout << "You cannot escape the final boss!\n";
                continue;
            }

            if (rand() % 2 == 0)
            {
                cout << "You escaped successfully!\n";
                return;
            }

            cout << "Escape failed!\n";
        }

        if (enemy.hp > 0)
        {
            int damage = max(1, enemy.attack
                                - player.defense
                                + rand() % 5);

            player.hp = max(0, player.hp - damage);

            cout << enemy.name << " dealt "
                 << damage << " damage to you!\n";
        }
    }

    if (player.hp <= 0)
    {
        finishGame(false);
        return;
    }

    cout << "\nYou defeated " << enemy.name << "!\n";
    player.gold += enemy.goldReward;
    player.addXP(enemy.xpReward);

    cout << "Rewards: " << enemy.xpReward << " XP and "
         << enemy.goldReward << " gold.\n";

    if (boss)
    {
        finishGame(true);
    }
}

void Game::usePotion()
{
    if (player.potions <= 0)
    {
        cout << "You have no health potions!\n";
        return;
    }

    if (player.hp == player.maxHp)
    {
        cout << "Your health is already full!\n";
        return;
    }

    player.potions--;

    int healing = min(40, player.maxHp - player.hp);
    player.hp += healing;

    cout << "You recovered " << healing << " HP.\n";
    cout << "Current HP: " << player.hp << "/"
         << player.maxHp << "\n";
}

void Game::showInventory()
{
    cout << "\n========== INVENTORY ==========\n";
    cout << "Weapon: " << player.weapon << "\n";
    cout << "Health Potions: " << player.potions << "\n";
    cout << "Gold: " << player.gold << "\n";
    cout << "================================\n";
}

void Game::saveGame()
{
    ofstream file("data/savegame.txt");

    if (!file)
    {
        cout << "Could not save game. Check the data folder.\n";
        return;
    }

    file << player.name << '\n'
         << player.weapon << '\n'
         << player.level << '\n'
         << player.hp << '\n'
         << player.maxHp << '\n'
         << player.attack << '\n'
         << player.defense << '\n'
         << player.gold << '\n'
         << player.xp << '\n'
         << player.potions << '\n'
         << player.room << '\n';

    if (!file)
    {
        cout << "An error occurred while saving the game.\n";
        return;
    }

    cout << "Game saved successfully!\n";
}

bool Game::loadGame()
{
    ifstream file("data/savegame.txt");

    if (!file)
        return false;

    Player loaded;

    if (!getline(file, loaded.name) ||
        !getline(file, loaded.weapon) ||
        !(file >> loaded.level
               >> loaded.hp
               >> loaded.maxHp
               >> loaded.attack
               >> loaded.defense
               >> loaded.gold
               >> loaded.xp
               >> loaded.potions
               >> loaded.room))
    {
        return false;
    }

    if (loaded.name.empty() ||
        loaded.level < 1 ||
        loaded.maxHp < 1 ||
        loaded.hp < 1 ||
        loaded.hp > loaded.maxHp ||
        loaded.attack < 0 ||
        loaded.defense < 0 ||
        loaded.gold < 0 ||
        loaded.xp < 0 ||
        loaded.potions < 0 ||
        loaded.room < 1 ||
        loaded.room > 5)
    {
        return false;
    }

    player = loaded;
    playerCreated = true;
    gameOver = false;

    cout << "Welcome back, " << player.name << "!\n";
    player.showStats();

    return true;
}

void Game::finishGame(bool victory)
{
    gameOver = true;

    if (victory)
    {
        cout << "\n========================================\n";
        cout << "             VICTORY!                   \n";
        cout << "========================================\n";
        cout << "Congratulations, " << player.name << "!\n";
        cout << "You defeated the Dungeon Dragon!\n";
        cout << "You have conquered the dungeon!\n";
    }
    else
    {
        cout << "\n========================================\n";
        cout << "              GAME OVER                 \n";
        cout << "========================================\n";
        cout << player.name << " was defeated in the dungeon.\n";
    }

    cout << "Final Level: " << player.level << "\n";
    cout << "Gold Collected: " << player.gold << "\n";
    cout << "========================================\n";

    playerCreated = false;
    pause();
}