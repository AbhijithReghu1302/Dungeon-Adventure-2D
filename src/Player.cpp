#include <iostream>
#include "../include/Player.h"

using namespace std;

Player::Player()
{
    name = "Unknown";

    level = 1;
    health = 100;
    maxHealth = 100;
    attack = 20;
    defense = 10;
    gold = 50;
    experience = 0;
}

void Player::createPlayer(const string& playerName)
{
    name = playerName;
}

void Player::displayStats() const
{
    cout << "\n";
    cout << "========================================\n";
    cout << "             PLAYER STATS               \n";
    cout << "========================================\n";

    cout << "Name       : " << name << "\n";
    cout << "Level      : " << level << "\n";
    cout << "Health     : " << health << "/" << maxHealth << "\n";
    cout << "Attack     : " << attack << "\n";
    cout << "Defense    : " << defense << "\n";
    cout << "Gold       : " << gold << "\n";
    cout << "Experience : " << experience << "\n";

    cout << "========================================\n";
}

void Player::addGold(int amount)
{
    gold += amount;
}