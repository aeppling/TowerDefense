#ifndef GAME_HPP_
#define GAME_HPP_

#include "Tower.hpp"
#include "TDUnit.hpp"
#include "RetrieveLevel.hpp"
#include "usefullStruct.hpp"

#include <iostream>

class Tower;

class Game{
    private : 
        int difficulty;
        int lifeNumber;
        int currentWaveNumber;
        Point baseCoord;
        std::vector<MapCell> spawnCells;
        int coinNumber;
        std::vector<std::vector<TDUnit *>> enemyList;
        std::vector<Tower *> towerList;
        RetrieveLevel        *levelRetriever;
    public :
        Game(int difficulty, int level);
        void loop();
        bool gameEnd();
        void gameWon();
        void gameLost();
        void startWave();
        int  getCurrentWaveNumber() { return (this->currentWaveNumber); };
        void activateTowers();
        void deactivateTowers();
        void createTower();
        bool canBuy(Tower &tower, int level);
        bool canPlace(Tower &tower, int xPos, int yPos);
        void addCoins(int number);
        void startLevel();
        bool waveEnd();
        void display();
        bool enemyAtBase();
        void upgradeTower(Tower &tower);
    };

#endif // GAME_HPP_