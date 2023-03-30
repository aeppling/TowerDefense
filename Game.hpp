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
        bool testMap(std::string path, MapCell *baseCell, std::vector<MapCell*> &spawnCells);
        void setUnitsTextures(SFMLLoader &sfmlLoader, std::vector<std::vector<TDUnit*>> &enemyList,
                              int winSizeX, int winSizeY, int mapSizeX, int mapSizeY);
        int loop(SFMLLoader &sfmlLoader, sf::RenderWindow &window, std::vector<MapCell*> spawnCells,
                 MapCell *baseCell, TDMap &map);
        int launch(SFMLLoader &sfmlLoader, sf::RenderWindow &window);
        void runWindowLevelLoop(sf::RenderWindow &window, TDMap &map, MapCell *baseCell,
                            std::vector<std::vector<TDUnit *>> &enemyList, SFMLLoader &sfmlLoader);
        void setObstacleTest(TDMap &map, sf::RenderWindow &window, SFMLLoader sfmlLoader);
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