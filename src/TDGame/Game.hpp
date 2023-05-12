#ifndef GAME_HPP_
#define GAME_HPP_

#include "../TDTowers/Tower.hpp"
#include "../TDUnits/TDUnit.hpp"
#include "RetrieveLevel.hpp"
#include "usefullStruct.hpp"
#include "Buildable.hpp"
#include "SizeRatioCalculator.hpp"
#include "../TDGraphics/SFMLTowerLoader.hpp"
#include "../TDGraphics/SFMLEnemiesLoader.hpp"
#include "../TDGraphics/SFMLMissileLoader.hpp"
#include "../TDPlayer/TDPlayer.hpp"
#include "../TDGraphics/SFMLCoinAnimation.hpp"
#include "../TDGraphics/SFMLHud.hpp"
#include "../TDSounds/SFMainSoundPlayer.hpp"
#include "../TDSounds/SFTowerSoundLoader.hpp"
#include <iostream>
#include "NetworkController.hpp"

class Tower;
class SFMLHud;

class Game{
    struct GameState {
    // Définition de la structure de données pour l'état du jeu
    int numCoins;
    std::vector<Tower*>* towerList;
    std::vector<Point> walls;

    };
    private : 
        int difficulty;
        int currentWaveNumber;
        int unitCount;
        int spawnCount;
        int cellSize;
        int planet;
        int level;
        int towerSelectorIndex;
        int nb_tower_type = 6;
        int globalVolume;
        int isMuted;
        Point baseCoord;
        std::vector<MapCell*> spawnCells;
        std::vector<sf::Sprite> spawnCellsSprites;
        int enemiesLeft;
        int totalEnemies;
        TDPlayer *player;
        MapCell *baseCellObject;
        SpritesHolder spritesHolder;
        std::shared_ptr<SpritesHolder> spritesHolderPtr;
        std::vector<std::vector<TDUnit *>> enemyList;
        std::shared_ptr<std::vector<TDUnit*>> currentWave;
        std::vector<Tower *> towerList;
        std::vector<std::vector<Tower *>> towerStoreList;
        Tower                *selectedActiveTower;
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
        SFMLHud*            sfmlHud;
        SFMLDecorationLoader sfmlDecorationLoader;
        SFMainSoundPlayer   &sfMainSoundPlayer;
        SFTowerSoundLoader  &sfTowerSoundLoader;
        NetworkController*  networkController;
        sf::Sprite          hearthDisplay;
        sf::Sprite          baseCell;
        sf::RectangleShape  hitMarker;
        unsigned int        hitMarkerOpacity;
        bool                isCursorOutsideMap;
        int                 mapMaxPosX;
        int                 mapMaxPosY;
        std::chrono::steady_clock::time_point hitMarkerStartTimer;
        std::chrono::steady_clock::time_point endWaveTransitionTimer;
        bool                isWaveEnding;
        GameState           gameState;
        int                 id;

    public :
        Game(int difficulty, int level, TDPlayer *player1, SFMainSoundPlayer &sfMainSoundPlayer1, SFTowerSoundLoader &towerSoundLoader, NetworkController* networkController, int planetToLoad);
        ~Game() { this->cleanAll(); };
        bool testMap(std::string path, MapCell *baseCell, std::vector<MapCell*> &spawnCells);
    void initializeTowerStore(sf::RenderWindow &window);
    void initializeTowerStoreCurrentWave();
        void setUnitsTextures(SFMLLoader &sfmlLoader, std::vector<std::vector<TDUnit*>> &enemyList,
                              int winSizeX, int winSizeY, int mapSizeX, int mapSizeY);
        int loop(SFMLLoader &sfmlLoader, sf::RenderWindow &window, MapCell *baseCell, TDMap &map, SpritesHolder &spritesHolder);
        int launch(SFMLLoader &sfmlLoader, sf::RenderWindow &window, int globalVolume);
        void runWindowLevelLoop(sf::RenderWindow &window, TDMap &map, MapCell *baseCell,
                            std::vector<std::vector<TDUnit *>> &enemyList, SFMLLoader &sfmlLoader);
        void setObstacleTest(TDMap &map, sf::RenderWindow &window);
        bool setTowerTest(TDMap &map, sf::RenderWindow &window, Buildable *toBuild, bool isWaveRunning);
        bool gameEnd();
        void gameWon();
        void gameLost();
        void cleanAll();
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
        void setAllHoveringSprites(TDMap &map, sf::RenderWindow &window, int posX, int posY, bool showBuildable, Tower *towerInfos);
        void setHoveringSprites(sf::RenderWindow &window, int posX, int posY, int radius, bool isBuildable, int fade);
        void setHoveringBuildable(sf::RenderWindow &window, int posX, int posY, sf::Sprite *buildableSprite);
        void display();
        void displayCoins(sf::RenderWindow &window);
        void displayTowers(sf::RenderWindow &window, MapCell *baseCell);
        void displayExplosions(sf::RenderWindow &window);
        bool enemyAtBase();
        void sellTower(TDMap &map);
        void upgradeTower();
        void towerMouseHovering(TDMap &map, sf::RenderWindow &window);
        void isTowerClicked(TDMap &map, sf::RenderWindow &window, mouseCoordinates &mouseCoord);
        bool isOnPath(MapCell *cell);
        bool checkCursorOutsideMap(int posX, int posY, TDMap &map);
        void setSpawnCellsSprites();
        void sendGameStateToClients();
        void handleUpdateGameState(TDMap &map, sf::RenderWindow &window, bool* isWaveRunning);
        void pauseMenu(bool pause);
    };

#endif // GAME_HPP_