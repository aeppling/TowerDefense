#ifndef GAME_HPP_
#define GAME_HPP_

#include "../TDTowers/Tower.hpp"
#include "../TDUnits/TDUnit.hpp"
#include "RetrieveLevel.hpp"
#include "usefullStruct.hpp"
#include "Buildable.hpp"
#include "../TDGraphics/SFMLTowerLoader.hpp"
#include "../TDGraphics/SFMLEnemiesLoader.hpp"
#include "../TDGraphics/SFMLMissileLoader.hpp"
#include "../TDPlayer/TDPlayer.hpp"
#include "../TDGraphics/SFMLCoinAnimation.hpp"

#include <iostream>

class Tower;

class Game{
    private : 
        int difficulty;
        int currentWaveNumber;
        int unitCount;
        int spawnCount;
        int cellSize;
        int towerSelectorIndex;
        Point baseCoord;
        std::vector<MapCell*> spawnCells;
        int enemiesLeft;
        int totalEnemies;
        TDPlayer *player;
        MapCell *baseCellObject;
        SpritesHolder spritesHolder;
        std::shared_ptr<SpritesHolder> spritesHolderPtr;
        std::vector<std::vector<TDUnit *>> enemyList;
        std::shared_ptr<std::vector<TDUnit*>> currentWave;
        std::vector<Tower *> towerList;
        std::vector<Tower *> towerStoreList;
        RetrieveLevel        *levelRetriever;
        sf::Text             waveCounterDisplay;
        sf::Text             enemiesLeftDisplay;
        sf::Text             lifeCounterDisplay;
        sf::Text             killCounterDisplay;
        sf::Text             infoBoxDisplay;
        SFMLEnemiesLoader   sfmlEnemiesLoader;
        SFMLTowerLoader     sfmlTowerLoader;
        SFMLMissileLoader   sfmlMissileLoader;
        SFMLCoinAnimation   sfmlCoinAnimation;
        SFMLLoader          sfmlLoaderMap;
        sf::Sprite          hearthDisplay;
        sf::Sprite          baseCell;
        sf::RectangleShape  hitMarker;
        unsigned int       hitMarkerOpacity;
    std::chrono::steady_clock::time_point hitMarkerStartTimer;
    public :
        Game(int difficulty, int level, TDPlayer *player1);
        bool testMap(std::string path, MapCell *baseCell, std::vector<MapCell*> &spawnCells);
    void initializeTowerStore();
    void initializeTowerStoreCurrentWave();
        void setUnitsTextures(SFMLLoader &sfmlLoader, std::vector<std::vector<TDUnit*>> &enemyList,
                              int winSizeX, int winSizeY, int mapSizeX, int mapSizeY);
        int loop(SFMLLoader &sfmlLoader, sf::RenderWindow &window, MapCell *baseCell, TDMap &map, SpritesHolder &spritesHolder);
        int launch(SFMLLoader &sfmlLoader, sf::RenderWindow &window);
        void runWindowLevelLoop(sf::RenderWindow &window, TDMap &map, MapCell *baseCell,
                            std::vector<std::vector<TDUnit *>> &enemyList, SFMLLoader &sfmlLoader);
        void setObstacleTest(TDMap &map, sf::RenderWindow &window);
        bool setTowerTest(TDMap &map, sf::RenderWindow &window, Buildable *toBuild, bool isWaveRunning);
        bool gameEnd();
        void gameWon();
        void gameLost();
        void startWave(TDMap &map, MapCell *baseCell, std::vector<MapCell*> &spawnCells);
        int  getCurrentWaveNumber() { return (this->currentWaveNumber); };
        void activateTowers();
        void deactivateTowers();
        void createTower();
        bool isBuildableAtPosition(TDMap &map, int x, int y, int size);
        bool isBuildableAtPositionForSmaller(TDMap &map, int x, int y, int size);
        bool canBuy(Tower &tower, int level);
        bool canPlace(Tower &tower, int xPos, int yPos);
        void addCoins(int number);
        void looseCoins(int number);
        void startLevel();
        void drawInfoBox(sf::RenderWindow& window, const sf::Vector2f& rectSize, const std::string& textString, bool display);
        bool waveEnd(sf::RenderWindow& window);
        void setHoveringSprites(sf::RenderWindow &window, int posX, int posY, int radius, bool isBuildable);
        void display();
        void displayCoins(sf::RenderWindow &window);
        void displayMapAndTowers(sf::RenderWindow &window, MapCell *baseCell);
        bool enemyAtBase();
        void upgradeTower(Tower &tower);
    };

#endif // GAME_HPP_