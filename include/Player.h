#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
private:
    std::string name;

    int level;
    int health;
    int maxHealth;
    int attack;
    int defense;
    int gold;
    int experience;

public:
    Player();

    void createPlayer(const std::string& playerName);
    void displayStats() const;

    void addGold(int amount);
};

#endif