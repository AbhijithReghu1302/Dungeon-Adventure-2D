#ifndef GAME_H
#define GAME_H

#include <string>

class Player
{
public:
    std::string name;
    std::string weapon = "Iron Sword";

    int level = 1;
    int hp = 100;
    int maxHp = 100;
    int attack = 20;
    int defense = 8;
    int gold = 50;
    int xp = 0;
    int potions = 3;
    int room = 1;

    void showStats() const;
    void addXP(int amount);
};

class Enemy
{
public:
    std::string name;
    int hp;
    int attack;
    int defense;
    int xpReward;
    int goldReward;
};

class Dungeon
{
public:
    Enemy createEnemy(bool boss, int level) const;
};

class Game
{
private:
    Player player;
    Dungeon dungeon;
    bool playerCreated = false;
    bool gameOver = false;

    void showMainMenu();
    void startNewGame();
    void showAdventureMenu();
    void exploreDungeon();
    void battle(bool boss);
    void usePotion();
    void saveGame();
    bool loadGame();
    void showInventory();
    void finishGame(bool victory);
    int readChoice(int min, int max);
    void pause();

public:
    void start();
};

#endif