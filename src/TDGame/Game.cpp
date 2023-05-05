#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Game.hpp"
#include "../TDGraphics/SFMLMapReloader.hpp"
#include "../TDTowers/AntiAirTower.hpp"
#include "../TDTowers/BasicTower.hpp"
#include "../TDTowers/AttackSpeedTower.hpp"
#include "../TDTowers/SlowTower.hpp"
#include "../TDTowers/SniperTower.hpp"
#include "../TDTowers/SplashTower.hpp"
#include "../TDGame/usefullStruct.hpp"

Game::Game(int difficulty, int level, TDPlayer *player1){
    this->level = level;
    SFMLEnemiesLoader sfmlEnemiesLoader;
    SFMLTowerLoader sfmlTowerLoader;
    SFMLMissileLoader sfmlMissileLoader;
    SFMLCoinAnimation sfmlCoinAnimation;
    SFMLLoader sfmlLoader;
    SFMLDecorationLoader decorationLoader;
    this->sfmlDecorationLoader = decorationLoader;
    this->sfmlLoaderMap = sfmlLoader;
    this->sfmlMissileLoader = sfmlMissileLoader;
    this->sfmlEnemiesLoader = sfmlEnemiesLoader;
    this->sfmlTowerLoader = sfmlTowerLoader;
    this->sfmlCoinAnimation = sfmlCoinAnimation;
    this->levelRetriever = new RetrieveLevel(this->level);
    this->difficulty = difficulty;
    this->baseCoord = {0,0};
    this->player = player1;
    this->player->setLifeNumber(8/difficulty);
    this->player->setCoinNumber(500-(difficulty*100));
    this->currentWaveNumber = 0;
    std::vector<MapCell> spawnCells;
    this->enemyList = this->levelRetriever->getNextLevel();
    this->unitCount = 0;
    this->spawnCount = 0;
    this->towerSelectorIndex = 0;
    this->spritesHolderPtr = std::make_shared<SpritesHolder>(this->spritesHolder);
    this->hitMarker.setSize(sf::Vector2f(1920, 1280));
    sf::Color hitMarkerColor(255, 0, 0, 0);
    this->hitMarker.setFillColor(hitMarkerColor);
    this->hitMarkerOpacity = 0;
    this->selectedActiveTower = nullptr;
}


void displayDebugMap2(std::vector<std::vector<MapCell>> *map) {
    int x;
    int y = 0;

    int firstLine = 0;
    std::cout << "     ";
    while (firstLine != map->at(0).size()) {
        std::cout << firstLine << " ";
        firstLine++;
    }
    std::cout << std::endl;
    while (y != map->size()) {
        x = 0;
        if (y < 10)
            std::cout << y << " :  ";
        else
            std::cout << y << " : ";
        while (x != (*map)[y].size()) {
            std::cout << (*map)[y][x].getType() << " ";
            x++;
        }
        std::cout << std::endl;
        y++;
    }

    std::cout << "END OF DEBUG DISPLAY" << std::endl << std::endl;

}

bool    Game::testMap(std::string path, MapCell *baseCell, std::vector<MapCell*> &spawnCells) {
    std::ifstream   file(path);
    int             line_count = 0;
    bool            isBaseFound = false;
    bool            isSpawnFound = false;
    int             mapWidth = -1;

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            if (mapWidth == -1)
                mapWidth = line.length();
            else {
                if (mapWidth != line.length()) {
                    std::cout << "Error on map : Every line should be of the same width." << std::endl;
                    return (false);
                }
            }
            int i = 0;
            while (i != line.length()) {
                if (line[i] == 'B') {
                    if (isBaseFound == true) {
                        std::cout << "Error on map : Multiples bases found. Should be only 1 per map" << std::endl;
                        return (false);
                    }
                    else {
                        baseCell->setPosX(i * 3);
                        baseCell->setPosY(line_count * 3);
                        isBaseFound = true;
                    }
                }
                if (line[i] == 'S') {
                    isSpawnFound = true;
                    spawnCells.push_back(new MapCell('S', i * 3, line_count * 3));
                }
                std::cout << line[i++];
            }
            std::cout << std::endl;
            line_count++;
        }
        if ((isBaseFound == false) || (isSpawnFound == false)) {
            std::cout << "Error on map : No bases found or no spawn found." << std::endl;
            return (false);
        }
        else
            return (true);
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }
    file.close();
}

void Game::initializeTowerStore(sf::RenderWindow &window) {
    this->towerStoreList.clear();
    int y = 0;
    while (y <= 5) {
        std::vector<Tower *> newVector;
        this->towerStoreList.push_back(newVector);
        y++;
    }
    int i = 0;
    while (i <= 1) {
        Tower *buildTowerType1 = new BasicTower(this, this->cellSize, this->sfmlTowerLoader, this->sfmlMissileLoader,
                                                window);
        Tower *buildTowerType2 = new AttackSpeedTower(this, this->cellSize, this->sfmlTowerLoader,
                                                      this->sfmlMissileLoader, window);
        Tower *buildTowerType3 = new AntiAirTower(this, this->cellSize, this->sfmlTowerLoader, this->sfmlMissileLoader,
                                                  window);
        Tower *buildTowerType4 = new SlowTower(this, this->cellSize, this->sfmlTowerLoader, this->sfmlMissileLoader,
                                               window);
        Tower *buildTowerType5 = new SniperTower(this, this->cellSize, this->sfmlTowerLoader, this->sfmlMissileLoader,
                                                 window);
        Tower *buildTowerType6 = new SplashTower(this, this->cellSize, this->sfmlTowerLoader, this->sfmlMissileLoader,
                                                 window);
        this->towerStoreList.at(0).push_back(buildTowerType1);
        this->towerStoreList.at(1).push_back(buildTowerType2);
        this->towerStoreList.at(2).push_back(buildTowerType3);
        this->towerStoreList.at(3).push_back(buildTowerType4);
        this->towerStoreList.at(4).push_back(buildTowerType5);
        this->towerStoreList.at(5).push_back(buildTowerType6);
        i++;
    }
    this->initializeTowerStoreCurrentWave();
}

void Game::initializeTowerStoreCurrentWave() {
    int y = 0;
    while (y <= 5) {
        int i = 0;
        while (i < this->towerStoreList.at(y).size()) {
            this->towerStoreList.at(y).at(i)->setCurrentWave(this->currentWave);
            i++;
        }
        y++;
    }
}

void Game::setUnitsTextures(SFMLLoader &sfmlLoader, std::vector<std::vector<TDUnit*>> &enemyList,
                      int winSizeX, int winSizeY, int mapSizeX, int mapSizeY) {
    int wave_count = 0;
    int unit_count = 0;
    while (wave_count != enemyList.size()) {
        unit_count = 0;
        while (unit_count != enemyList.at(wave_count).size()) {
            enemyList.at(wave_count).at(unit_count)->setSprite(this->sfmlEnemiesLoader, winSizeX, winSizeY, mapSizeX, mapSizeY, this->cellSize);
            unit_count++;
        }
        wave_count++;
    }
}

void Game::isTowerClicked(TDMap &map, sf::RenderWindow &window, mouseCoordinates &mouseCoord) {
    int i = 0;
    while (i < this->towerList.size()) {
        int posX = this->towerList.at(i)->getPosition().x;
        int posY = this->towerList.at(i)->getPosition().y;
        if ((mouseCoord.posX == posX || mouseCoord.posX == posX + 1 || mouseCoord.posX == posX - 1)
            && (mouseCoord.posY == posY || mouseCoord.posY == posY + 1 || mouseCoord.posY == posY - 1)) {
            this->selectedActiveTower = this->towerList.at(i);
            this->sfmlHud->setSelectedTower(this->selectedActiveTower);
            break;
        }
        else if (mouseCoord.posX > map.getSizeX()) {
            break;
        }
        else {
            this->selectedActiveTower = nullptr;
            this->sfmlHud->setSelectedTower(this->selectedActiveTower);
        }
        i++;
    }
}

void Game::towerMouseHovering(TDMap &map, sf::RenderWindow &window) {
    mouseCoordinates mouseCoord = getMouseCellCoordinate(map, window);
    int i = 0;
    while (i < this->towerList.size()) {
        int posX = this->towerList.at(i)->getPosition().x;
        int posY = this->towerList.at(i)->getPosition().y;
        if ((mouseCoord.posX == posX || mouseCoord.posX == posX + 1 || mouseCoord.posX == posX - 1)
            && (mouseCoord.posY == posY || mouseCoord.posY == posY + 1 || mouseCoord.posY == posY - 1)) {
            this->setAllHoveringSprites(map, window, this->towerList.at(i)->getPosition().x, this->towerList.at(i)->getPosition().y, false, this->towerList.at(i));
            break;
        }
        i++;
    }
}

bool Game::checkCursorOutsideMap(int posX, int posY, TDMap &map) {
    if ((posX >= map.getSizeX()) || (posY >= map.getSizeY()))
        return (true);
    else
        return (false);
}

void Game::sellTower(TDMap &map) {
    int i = 0;
    while (i < this->towerList.size()) {
        if (this->selectedActiveTower == this->towerList.at(i)) {
            int cost = this->towerList.at(i)->getCost() / 2;
            this->addCoins(cost);
            this->sfmlCoinAnimation.launchCoinsAnimation(this->cellSize, this->towerList.at(i)->getPosition().x, this->towerList.at(i)->getPosition().y, cost, true);
            this->towerList.at(i)->deactivate();
            map.getElem(this->towerList.at(i)->getPosition().x, this->towerList.at(i)->getPosition().y)->setType('T');
            this->towerList.erase(this->towerList.begin() + i);
            this->selectedActiveTower = nullptr;
            this->sfmlHud->setSelectedTower(nullptr);
            break;
        }
        i++;
    }
}

void Game::upgradeTower() {
    int i = 0;

    while (i < this->towerList.size()) {
        if (this->selectedActiveTower == this->towerList.at(i)) {
            int cost = this->towerList.at(i)->getUpgradeCost();
         //   if (cost <= this->player->getCoinNumber()){
                this->looseCoins(cost);
                this->sfmlCoinAnimation.launchCoinsAnimation(this->cellSize, this->towerList.at(i)->getPosition().x, this->towerList.at(i)->getPosition().y, cost, false);
                this->towerList.at(i)->upgrade(this->sfmlTowerLoader);
           // }
            break;
        }
        i++;
    }
}

void runUnit(std::vector<std::vector<TDUnit*>> &enemyList, TDMap &map, unsigned int &basePosX,
              unsigned int &basePosY, unsigned int wave, std::vector<MapCell*> &spawnCells, int unitCount, int spawnCount) {
    // RUN EVERY UNIT THREADS
    std::vector<std::vector<MapCell>> *nmap = map.getMapVector();
    enemyList.at(wave).at(unitCount)->setPosX(spawnCells.at(spawnCount)->getPosX());
    enemyList.at(wave).at(unitCount)->setPosY(spawnCells.at(spawnCount)->getPosY());
    enemyList.at(wave).at(unitCount)->searchPath(nmap, basePosX, basePosY);
    enemyList.at(wave).at(unitCount)->run(&map);
}

int Game::loop(SFMLLoader &sfmlLoader, sf::RenderWindow &window, MapCell *baseCell, TDMap &map, SpritesHolder &spritesHolder){
            startLevel();
            bool isBuilding = false;
            int timeBetweenSpawn = 1200;
            int cellSize = getCellSize(window.getSize().x, window.getSize().y, map.getSizeX(), map.getSizeY());
            // SETTING UP MOUSE POINTER
            window.setMouseCursorVisible(false);
            sf::Texture mousePointerTexture;
            mousePointerTexture.loadFromFile("Sprites/Cursors/crosshair043.png");
            sf::Sprite mousePointer(mousePointerTexture);
            float scaleFactor = static_cast<float>(cellSize) / static_cast<float>(144);
            sf::IntRect textureRect(0, 0, 144, 144);
            mousePointer.setScale(scaleFactor * 2, scaleFactor * 2);
            mousePointer.setTextureRect(textureRect);
            bool closing = false;
            while ((this->gameEnd() != true) && window.isOpen()) {  // RUN WHILE GAME IS NOT END OR WINDOW OPEN
                std::chrono::steady_clock::time_point waveChronoStart = std::chrono::steady_clock::now();
                bool isWaveRunning = false;
                // CREATE SHARED PTR OF WAVE HERE
                this->towerStoreList.clear();
                this->currentWave.reset();
                this->currentWave = nullptr;
                this->currentWave = std::make_shared<std::vector<TDUnit*>>(this->enemyList[this->currentWaveNumber]);
                this->startWave(map, baseCell, spawnCells); // RUN UNITS & TOWERS
                std::cout << "Wave Started" << std::endl;
                this->unitCount = 0; // UNIT & SPAWN COUNTER FOR SPAWNING
                this->spawnCount = 0;
                Buildable *toBuild = nullptr;
                // PROBLEM IS I RE-ASSIGN NEW TOURS ? BUT THE WORKING TOURS IS ON TOO
                std::cout << "Wave contain " << this->currentWave->size() << " ennemies" << std::endl;
                this->enemiesLeft = this->currentWave->size();
                this->enemiesLeftDisplay.setString("Enemies left : " + std::to_string(this->enemiesLeft));
                this->totalEnemies = this->currentWave->size();
                this->lifeCounterDisplay.setString("Your life : " + std::to_string(this->player->getLifeNumber()));
                //SET TOWER CURRENT WAVE HERE
             //   Tower *buildTowerTest = new AntiAirTower(this, this->cellSize, this->sfmlTowerLoader);
                // ATTACK SPEED TOWER CRASH
              //  Tower *buildTowerTest2 = new AttackSpeedTower(this, this->cellSize, this->sfmlTowerLoader);
              // INITIALIZE TOWER STORE LIST
                this->initializeTowerStore(window);
                //
                this->sfmlHud->setTowerStoreList(this->towerStoreList);
                usleep(3000);
                while (!this->waveEnd(window)) { // RUN WHILE WAVE IS NOT FINISHED
                    std::chrono::steady_clock::time_point testTime = std::chrono::steady_clock::now(); // SET CURRENT ELAPSED TIME ON WAVE
                    int waveChronoElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(testTime - waveChronoStart).count();
                    if (isWaveRunning) {
                        if ((waveChronoElapsed >= timeBetweenSpawn) && (this->unitCount != this->enemyList.at(
                                this->currentWaveNumber).size())) { // RUN A UNIT IF ENOUGH TIME ELAPSED
                            unsigned int basePosX = baseCell->getPosX();
                            unsigned int basePosY = baseCell->getPosY();
                            runUnit(std::ref(this->enemyList), std::ref(map), std::ref(basePosX), std::ref(basePosY),
                                    std::ref(this->currentWaveNumber), this->spawnCells, this->unitCount,
                                    this->spawnCount);
                            this->spawnCount++;
                            this->unitCount++;
                            if (this->spawnCount >= this->spawnCells.size())
                                this->spawnCount = 0;
                            waveChronoStart = std::chrono::steady_clock::now();
                        }
                    }
                    // REFRESH WINDOW AND INTERCEPT EVENTS
                    sf::Event event;
                    window.clear(sf::Color::Black);
                    while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                            window.close();
                            closing = true;
                            break;
                        }
                        if ((event.type == sf::Event::KeyPressed &&
                            event.key.code == sf::Keyboard::Enter) && (isWaveRunning == false)) {
                            this->activateTowers();
                            isWaveRunning = true;
                        }
                        if ((event.type == sf::Event::KeyPressed &&
                            event.key.code == sf::Keyboard::Escape && this->sfmlHud->getPaused() == false)
                            ) {
                            //Pause Menu
                            this->sfmlHud->setPaused(true);
                            this->deactivateTowers();
                            isWaveRunning = false;
                            this->sfmlHud->update();
                            this->sfmlHud->draw();
                        }
                        if ((event.type == sf::Event::KeyPressed &&
                            event.key.code == sf::Keyboard::Space && this->sfmlHud->getPaused() == true)
                            ) {
                            //UNPause Menu
                            this->sfmlHud->setPaused(false);
                            this->activateTowers();
                            isWaveRunning = true;
                            this->sfmlHud->update();
                            this->sfmlHud->draw();
                        }
                        if (event.type == sf::Event::MouseButtonPressed &&
                            sf::Mouse::isButtonPressed(sf::Mouse::Right)) { // SWITCH BUILDING MODE ON/OFF
                            if (isBuilding == false) {
                                isBuilding = true;
                                this->sfmlHud->setSelectedTower(nullptr);
                                this->selectedActiveTower = nullptr;
                            }
                            else {
                                //toBuild = nullptr;
                                isBuilding = false;
                               
                            }
                        }
                        mouseCoordinates mouseCoord = getMouseCellCoordinate(map, window);
                        if (isBuilding == true) {
                            this->isCursorOutsideMap = checkCursorOutsideMap(mouseCoord.posX, mouseCoord.posY, map);
                            if (event.type == sf::Event::MouseButtonPressed &&
                                sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // BUILD CURRENT BUILDABLE
                                setObstacleTest(std::ref(map), std::ref(window));
                                if (!this->towerStoreList.empty()) {
                                    if (this->towerSelectorIndex >= 0) {
                                        toBuild = this->towerStoreList.at(this->towerSelectorIndex).at(0);
                                        if (setTowerTest(std::ref(map), std::ref(window), toBuild, isWaveRunning)) {
                                            isBuilding = false;
                                            this->initializeTowerStore(window);
                                            this->sfmlHud->update();
                                        }
                                    }
                                }
                            }
                            if (event.type == sf::Event::KeyPressed) {
                                if (!this->towerStoreList.empty()) {
                                    if (event.key.code == sf::Keyboard::Right) {
                                        if (this->towerStoreList.size() <= 1)
                                            break;
                                        if (this->towerSelectorIndex >= (this->towerStoreList.size() - 1))
                                            this->towerSelectorIndex = 0;
                                        else
                                            this->towerSelectorIndex++;
                                    } else if (event.key.code == sf::Keyboard::Left) {
                                        if (this->towerStoreList.size() <= 1)
                                            break;
                                        if (this->towerSelectorIndex == 0) {
                                            this->towerSelectorIndex = this->towerStoreList.size() - 1;
                                        } else
                                            this->towerSelectorIndex--;
                                    }
                                }
                            }
                            if (event.type == sf::Event::KeyPressed &&
                                event.key.code == sf::Keyboard::T) {// TOWER BUILD TESTING -> SHOULD GO WITH WALL (UPPER IF) AFTER TEST OK
                               //OLD TOwER PLACEMENT
                            }
                        }
                        else {
                            if (event.type == sf::Event::MouseButtonPressed &&
                                sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // BUILD CURRENT BUILDABLE
                                this->isTowerClicked(map, window, mouseCoord);
                                if (this->selectedActiveTower != nullptr) {
                                    int clicked = this->sfmlHud->checkForSellUpgradeClick(window);
                                    if (clicked == 1)
                                        this->sellTower(map);
                                    else if (clicked == 2)
                                        this->upgradeTower();
                                }
                                else
                                    this->sfmlHud->checkForClick(window);
                            }
                        }
                    }
                    if (closing == true)
                        break;
                    int s = 0;
                    // DISPLAY MAP
                    this->spritesHolderPtr->displayMap(window, this->cellSize, this->sfmlLoaderMap);
                    if (isBuilding == false) {
                        if (this->selectedActiveTower != nullptr) {
                            this->setAllHoveringSprites(map, window, this->selectedActiveTower->getPosition().x, this->selectedActiveTower->getPosition().y, false, this->selectedActiveTower);
                        }
                        this->towerMouseHovering(map, window);
                    }
                    this->displayTowers(window, baseCell);
                    //DISPLAY BUILDING AREA (before enemies) and SHOOTING RANGE if tower building
                    if (isBuilding == true) {
                        mouseCoordinates mouseCoord = getMouseCellCoordinate(map, window);
                        if (!this->towerStoreList.empty()) {
                            try {
                                if (!(this->isCursorOutsideMap)) {
                                    if (this->towerSelectorIndex >= 0)
                                        this->setAllHoveringSprites(map, window, mouseCoord.posX, mouseCoord.posY, true,
                                                                    this->towerStoreList.at(
                                                                            this->towerSelectorIndex).at(0));
                                    else if (this->towerSelectorIndex == -2)
                                        this->setHoveringSprites(window, mouseCoord.posX, mouseCoord.posY, 0,
                                                                 this->isOnPath(
                                                                         map.getElem(mouseCoord.posX, mouseCoord.posY)),
                                                                 128);
                                }
                            }
                            catch (const std::out_of_range& ex){
                                std::cout << "Exception at line : " << __LINE__ << " in file : "<< __FILE__<< " : " << ex.what() << std::endl;

                            }
                        }
                    }
                    // DISPLAY ENNEMIES AND CHECK FOR ARRIVING == NOT TOO SOON !!!
                    if (isWaveRunning) {
                        s = 0;
                        while (s < enemyList.at(this->currentWaveNumber).size()) {
                            if (enemyList.at(this->currentWaveNumber).at(s)->isAtBase() == false) {
                                if (enemyList.at(this->currentWaveNumber).at(s)->getTypeName() == "Spaceship" && enemyList.at(this->currentWaveNumber).at(s)->getHealth() > 0) {
                                    sf::Sprite shipShadow(enemyList.at(this->currentWaveNumber).at(s)->getSprite());
                                    shipShadow.setPosition(enemyList.at(this->currentWaveNumber).at(s)->getSprite().getPosition().x - 10, enemyList.at(this->currentWaveNumber).at(s)->getSprite().getPosition().y + 15);//15 - 30
                                    shipShadow.setScale(shipShadow.getScale().x * 0.6, shipShadow.getScale().y * 0.6);
                                    shipShadow.setColor(sf::Color(0, 0, 0, 128));
                                    window.draw(shipShadow);
                                }
                                else if (enemyList.at(this->currentWaveNumber).at(s)->getTypeName() == "FlyingDrone" && enemyList.at(this->currentWaveNumber).at(s)->getHealth() > 0) {
                                    sf::Sprite droneShadow(enemyList.at(this->currentWaveNumber).at(s)->getSprite());
                                    droneShadow.setPosition(enemyList.at(this->currentWaveNumber).at(s)->getSprite().getPosition().x - 10, enemyList.at(this->currentWaveNumber).at(s)->getSprite().getPosition().y + 15);
                                    droneShadow.setScale(droneShadow.getScale().x * 0.9, droneShadow.getScale().y * 0.9);
                                    droneShadow.setColor(sf::Color(0, 0, 0, 128));
                                    window.draw(droneShadow);
                                }
                                window.draw(enemyList.at(this->currentWaveNumber).at(s)->getSprite());
                                if (enemyList.at(this->currentWaveNumber).at(s)->getHealth() > 0) {
                                    window.draw(enemyList.at(this->currentWaveNumber).at(s)->getMaxHealthBarSprite());
                                    window.draw(enemyList.at(this->currentWaveNumber).at(s)->getHealthBarSprite());
                                }
                            }
                            if ((enemyList.at(this->currentWaveNumber).at(s)->isAlive() == false)
                                && (enemyList.at(this->currentWaveNumber).at(s)->alreadyCounted() == false)) {
                                this->enemiesLeft--;
                                this->enemyList.at(this->currentWaveNumber).at(s)->setCounted();
                                this->player->addKill();
                                
                                std::cout << "Dead at position x:"
                                          << enemyList.at(this->currentWaveNumber).at(s)->getPosX();
                                std::cout << " y:" << enemyList.at(this->currentWaveNumber).at(s)->getPosY()
                                          << std::endl;
                                this->sfmlCoinAnimation.launchCoinsAnimation(cellSize,
                                                                             enemyList.at(this->currentWaveNumber).at(
                                                                                     s)->getPosX(),
                                                                             enemyList.at(this->currentWaveNumber).at(
                                                                                     s)->getPosY(),
                                                                             enemyList.at(this->currentWaveNumber).at(
                                                                                     s)->getValue(), true);
                                this->killCounterDisplay.setString(
                                        "Total kills : " + std::to_string(this->player->getTotalKill()));
                                this->enemiesLeftDisplay.setString(
                                        "Enemies left : " + std::to_string(this->enemiesLeft));
                                this->addCoins(enemyList.at(this->currentWaveNumber).at(s)->getValue());
                                this->sfmlHud->setMessage("You get coins when you kill enemies");

                            } else if (enemyList.at(this->currentWaveNumber).at(s)->isAtBase()) {
                                if ((map.getElem(this->enemyList.at(this->currentWaveNumber).at(s)->getPosX(),
                                                 this->enemyList.at(this->currentWaveNumber).at(
                                                         s)->getPosY())->getType() == 'B')
                                    && this->enemyList.at(this->currentWaveNumber).at(s)->alreadyArrived() == false) {
                                    this->enemyList.at(this->currentWaveNumber).at(s)->setAlreadyArrived();
                                    this->player->looseLife();
                                    this->sfmlHud->setMessage("Prevent enemies from reaching \nyour base to win the game");

                                    // RESET HIT MARKER OPACITY
                                    this->hitMarkerOpacity = 155;
                                    // DISPLAY HUD LIFE
                                    this->lifeCounterDisplay.setString(
                                            "Your life : " + std::to_string(this->player->getLifeNumber()));
                                    this->enemiesLeft--;
                                    if (this->player->getLifeNumber() <= 0)
                                        break;
                                }
                            }
                            s++;
                        }
                        this->displayExplosions(window);
                    }
                    else {
                        this->drawInfoBox(window, {700, 150}, "Press enter for next wave.", false);
                    }
                    // DISPLAY COINS
                    this->displayCoins(window);
                    // DISPLAY HIT MARKER
                    if (this->hitMarkerOpacity == 155) {
                        this->hitMarkerStartTimer = std::chrono::steady_clock::now();
                        this->hitMarkerOpacity--;
                    }
                    if (this->hitMarkerOpacity > 0) {
                        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                        if (std::chrono::duration_cast<std::chrono::milliseconds>(end - this->hitMarkerStartTimer).count() > 3) {
                            this->hitMarkerOpacity--;
                            this->hitMarkerStartTimer = std::chrono::steady_clock::now();
                        }
                        sf::Color hitMarkerColor(255, 0, 0, this->hitMarkerOpacity);
                        this->hitMarker.setFillColor(hitMarkerColor);
                        window.draw(this->hitMarker);
                    }
                    // BREAK IF DEAD
                    if (this->player->getLifeNumber() <= 0)
                        break;
                    // DISPLAY HUD
                    this->sfmlHud->setWave(this->currentWaveNumber);
                    this->sfmlHud->setMoney(this->player->getCoinNumber());
                    this->sfmlHud->setLives(this->player->getLifeNumber());
                    this->sfmlHud->update();
                    this->sfmlHud->draw();
                    if (event.type == sf::Event::MouseButtonPressed &&
                        sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // BUILD CURRENT BUILDABLE
                        int whichClicked = this->sfmlHud->checkForClick(window);
                        if (whichClicked != -1) {
                                this->towerSelectorIndex = whichClicked;
                               if (isBuilding == false)
                                   isBuilding = true;
                        }
                    }
                    // SET AND DISPLAY MOUSE
                    if ((isBuilding == true) && !(this->isCursorOutsideMap))
                        mousePointer.setColor(sf::Color::Transparent);
                    else
                        mousePointer.setColor(sf::Color::Blue);
                    sf::Vector2i mousePositionScreen = sf::Mouse::getPosition(window);
                    mousePointer.setPosition(mousePositionScreen.x -(cellSize - 3) + _GAME_POSITION_X, mousePositionScreen.y -(cellSize - 3) + _GAME_POSITION_Y);
                    window.draw(mousePointer);

                    // DISPLAY WAVE NUMBER
                    
                    //window.draw(this->hearthDisplay);
                    window.display();
                }
                if (this->player->getLifeNumber() <= 0) {
                    gameLost();
                    break;
                }
                else if (this->currentWaveNumber == this->enemyList.size()) {
                    gameWon();
                    break;
                }
               //WAVE ENDED
        }
}

void Game::setSpawnCellsSprites() {
    int i = 0;
    while (i < this->spawnCells.size()) {
        sf::Sprite newSprite;
        newSprite.setTexture(*this->sfmlLoaderMap.getSpawnBuilding());
        float scaleFactor = static_cast<float>(cellSize) / static_cast<float>(newSprite.getTexture()->getSize().x);
        sf::IntRect textureRect(0, 0, newSprite.getTexture()->getSize().x, newSprite.getTexture()->getSize().y);
        sf::Vector2f newOrigin(newSprite.getLocalBounds().width / 30.f, newSprite.getLocalBounds().height / 20.f);
        newSprite.setOrigin(newOrigin);
        newSprite.setScale(scaleFactor * 3, scaleFactor * 3);
        newSprite.setTextureRect(textureRect);
        newSprite.setPosition(this->spawnCells.at(i)->getPosX() * cellSize + _GAME_POSITION_X, this->spawnCells.at(i)->getPosY() * cellSize + _GAME_POSITION_Y);
        this->spawnCellsSprites.push_back(newSprite);
        i++;
    }
}

int Game::launch(SFMLLoader &sfmlLoader, sf::RenderWindow &window) {
    std::cout << "Launch HUD" << std::endl;
    this->sfmlHud = new SFMLHud(&sfmlLoader, &window, _GAME_POSITION_X, _GAME_POSITION_Y, 8/difficulty, currentWaveNumber, 500-(difficulty*100), this->enemyList.size(), this->level);
    
    sf::Texture hearthTexture;
    this->player->resetTotalKill();
    
    // GAME INITIALISATON
    // RETRIEVE ENEMY LIST (in consrtuctor for first wave)
    if (this->enemyList.size() == 0) {
        std::cout << "Couldn't retrieve level informations, leaving..." << std::endl;
        return (-1);
    }
    // TESTING MAP VALIDITY AND RETRIEVING SPAWN CELLS
    MapCell *baseCell = new MapCell('B', -1, -1);
    std::vector<MapCell*> spawnCells;
    if (testMap("level_1_map.txt", baseCell, spawnCells) == false) {
        std::cout << "Cannot load level : Map is not valid." << std::endl;
        return (-1);
    }
    //UNCOMMENT TO DEBUG SPAWNS
    /* int i = 0;
     while (i < spawnCells.size()) {
         std::cout << "Spawn : x:" << spawnCells[i]->getPosX() << " y:" << spawnCells[i]->getPosY() << std::endl;
         i++;
     }*/
    sf::Font mainFont;
    mainFont.loadFromFile("Fonts/neuropol.otf");
    this->infoBoxDisplay.setFont(mainFont);
    this->spawnCells = spawnCells;
    // MAP TEXTURE ARE SET IN SFMLLOAD WHILE CREATING MAP
   // SpritesHolder spritesHolder;
   // std::shared_ptr<SpritesHolder> spritesHolderPtr = std::make_shared<SpritesHolder>(spritesHolder);
    TDMap map("level_1_map.txt", sfmlLoader, window.getSize().x, window.getSize().y, this->spritesHolderPtr, this->sfmlDecorationLoader);
    // NOW SETTING UP UNIT TEXTURES AND CELL SIZE
    this->mapMaxPosX = map.getSizeX();
    this->mapMaxPosY = map.getSizeY();
    this->cellSize = getCellSize(window.getSize().x, window.getSize().y, map.getSizeX(), map.getSizeY());
    setSpawnCellsSprites();
    setUnitsTextures(sfmlLoader, this->enemyList, window.getSize().x, window.getSize().y, map.getSizeX(), map.getSizeY());
    this->baseCellObject = baseCell;
    this->baseCell.setTexture(*sfmlLoader.getBaseBuilding());
    this->baseCell.setPosition(baseCell->getPosX() * cellSize + _GAME_POSITION_X + 3, baseCell->getPosY() * cellSize + _GAME_POSITION_Y + 5);
    this->baseCell.setScale(1, 1);
    this->loop(sfmlLoader, window, baseCell, map, spritesHolder);
}

void Game::displayTowers(sf::RenderWindow &window, MapCell *baseCell) {
    int i = 0;
    while (i != this->towerList.size()) {
            sf::Sprite support;
            support.setTexture(*this->sfmlTowerLoader.getSupport());
            support.setPosition(this->towerList.at(i)->getTowerSprite().getPosition());
            sf::Vector2f newOrigin(support.getLocalBounds().width / 2.f, support.getLocalBounds().height / 2.f);
            support.setOrigin(newOrigin);
            support.setScale(1, 1);
            window.draw(support);
            window.draw(this->towerList.at(i)->getTowerSprite());
            int y = 0;
            while (y < this->towerList.at(i)->getTotalMissiles()) {
                window.draw(this->towerList.at(i)->getMissileSprite(y));
                window.draw(this->towerList.at(i)->getExplosionSprite(y));
                y++;
            }
            i++;
        }
    i = 0;
    while (i < this->spawnCellsSprites.size()) {
        window.draw(this->spawnCellsSprites.at(i));
        i++;
    }
    window.draw(this->baseCell);
}

void Game::displayExplosions(sf::RenderWindow &window) {
        int i = 0;
        while (i != this->towerList.size()) {
            int y = 0;
            while (y < this->towerList.at(i)->getTotalMissiles()) {
                if (this->towerList.at(i)->getExplosionSprite(y).getPosition().x != -1000)
                    window.draw(this->towerList.at(i)->getExplosionSprite(y));
                y++;
            }
            i++;
        }
}

void Game::displayCoins(sf::RenderWindow &window) {
    int i = 0;

    while (i < this->sfmlCoinAnimation.getTotalCoins()) {
        window.draw(this->sfmlCoinAnimation.getCoinFromIndex(i));
        i++;
    }
    i = 0;
    while (i < this->sfmlCoinAnimation.getTotalText()) {
        window.draw(this->sfmlCoinAnimation.getTextFromIndex(i));
        i++;
    }
}

void Game::startWave(TDMap &map, MapCell *baseCell, std::vector<MapCell*> &spawnCells){
    //* start the wave
    this->waveCounterDisplay.setString("Wave : " + std::to_string(this->currentWaveNumber + 1) + "/" + std::to_string(this->enemyList.size()));
    std::cout << "Starting wave" << currentWaveNumber << "/" << this->enemyList.size() << std::endl;
    std::cout << "Life number : " << this->player->getLifeNumber() << std::endl;
    std::cout << "Coin number : " << this->player->getLifeNumber() << std::endl;
    //* activate towers
//    this->activateTowers();
    // NO THREAD HERE BUT COUNTER IN MAIN LOOP AND CALL EVERY x SECONDS
}

bool Game::setTowerTest(TDMap &map, sf::RenderWindow &window, Buildable *toBuild, bool isWaveRunning) {
    mouseCoordinates mouseCoord = getMouseCellCoordinate(map, window);
    if (mouseCoord.posY >= 0 && mouseCoord.posY < map.getSizeY() && mouseCoord.posX >= 0 && mouseCoord.posX < map.getSizeX()) {
        // SET TOWER
        if (map.getElem(mouseCoord.posX, mouseCoord.posY)->getType() == 'T') { // CHECK IF TOWER BUILDABLE CELL
            // CHECK IF ENOUGH SPACE TO BUILD
            // i should already have a function to do this because of hoverring mouse area
            bool isBuildable = false;
            if (toBuild->getSize() - 1 <= 1) {
                isBuildable = isBuildableAtPositionForSmaller(map, mouseCoord.posX, mouseCoord.posY, toBuild->getSize() - 1);

            } else {
                isBuildable = isBuildableAtPosition(map, mouseCoord.posX, mouseCoord.posY, toBuild->getSize() - 1);
            }
            if ((isBuildable == true) || (toBuild->getSize() <= 1)) {
                // SET CURRENT CELL TO 'A' WITH OTHER CELL (FULL SIZE) (test if unit go through)
                map.getElem(mouseCoord.posX, mouseCoord.posY)->setType('A');
                // BUILD->Add tower with its coordinate to vector of actives towers
                Tower *toAdd = dynamic_cast<Tower *>(toBuild);
                if (toAdd == nullptr) {
                    std::cout << "Dynamic cast failed from Buidlable to Tower" << std::endl;
                    return (false);
                }
                this->towerList.push_back(toAdd);
                this->towerList[this->towerList.size() - 1]->setPosition(mouseCoord.posX, mouseCoord.posY, this->cellSize);
                this->looseCoins(toBuild->getCost());
                
                this->sfmlCoinAnimation.launchCoinsAnimation(cellSize, mouseCoord.posX,mouseCoord.posY, toBuild->getCost(), false);
                toBuild = nullptr;
                if (isWaveRunning == true)
                    this->towerList[this->towerList.size() - 1]->run(this->currentWave);
                map.refreshTextures(mouseCoord.posX, mouseCoord.posY);
//                this->towerStoreList.erase(this->towerStoreList.begin() + this->towerSelectorIndex);
                this->towerStoreList.at(this->towerSelectorIndex).erase(this->towerStoreList.at(this->towerSelectorIndex).begin());
                return (true);
            }
            else {
                return (false);
            }
        }
        else {
            return (false);
        }
    }
    else {
        return (false);
    }
}


void Game::setObstacleTest(TDMap &map, sf::RenderWindow &window) {
    mouseCoordinates mouseCoord = getMouseCellCoordinate(map, window);
    if (mouseCoord.posY >= 0 && mouseCoord.posY < map.getSizeY() && mouseCoord.posX >= 0 && mouseCoord.posX < map.getSizeX())
    {
        bool check = false;
        // SET WALL (WILL BE TOWER & WALL LATER)
        if (map.getElem(mouseCoord.posX, mouseCoord.posY)->getType() == 'X') {
            int count_spawn = 0;
            while (count_spawn < this->spawnCells.size()) {
                map.getElem(mouseCoord.posX, mouseCoord.posY)->setType('W');
                std::vector<std::vector<MapCell>> *nmap = map.getMapVector();
                AStarPathFinding pathFinder((*nmap), (*nmap)[this->spawnCells.at(count_spawn)->getPosY()][this->spawnCells.at(count_spawn)->getPosX()],
                                            (*nmap)[this->baseCellObject->getPosY()][this->baseCellObject->getPosX()]);
                std::vector<std::shared_ptr<MapCell>> pathtofill;
                if (pathFinder.runPathFinding(pathtofill, false, false) == false) {
                    map.getElem(mouseCoord.posX, mouseCoord.posY)->setType('X');
                    return;
                }
                count_spawn++;
            }
            this->looseCoins(5);
            this->sfmlCoinAnimation.launchCoinsAnimation(cellSize, mouseCoord.posX,mouseCoord.posY, 5, false);
            check = true;
        }
        else if (map.getElem(mouseCoord.posX, mouseCoord.posY)->getType() == 'W') {
            map.getElem(mouseCoord.posX, mouseCoord.posY)->setType('X');
            this->addCoins(2);
            this->sfmlCoinAnimation.launchCoinsAnimation(cellSize, mouseCoord.posX,mouseCoord.posY, 2, true);
            check = true;
        }
        if (check == false)
            return;
        map.refreshTextures(map.getElem(mouseCoord.posX, mouseCoord.posY)->getPosX(),
                            map.getElem(mouseCoord.posX, mouseCoord.posY)->getPosY());
        // ...
    }
}

bool Game::isBuildableAtPosition(TDMap &map, int x, int y, int size) {
    int maxY = map.getSizeY() - 1;
    int maxX = map.getSizeX() - 1;

    for (int i = -size; i <= size; i++) {
        for (int j = -size; j <= size; j++) {
            if (i == 0 && j == 0) { // CENTER ALREADY CHECKED
                continue;
            }
            int newY = y + i;
            int newX = x + j;
            // IS CHECKING NOT OUTSIDE MAP
            if (newY < 0 || newY > maxY || newX < 0 || newX > maxX) {
                continue;
            }
            if (map.getElem(newX, newY)->getType() != 'T') {
               if ((size == 1) && (i == -1 || i == 1 || j == -1 || j == 1)) { // 1 RADIUS IS DIFFERENT FROM OTHERS
                    continue;
                }
                else {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Game::isBuildableAtPositionForSmaller(TDMap &map, int x, int y, int size) {
    bool isBuildable = false;
    if (((x + size) > map.getSizeX()) || ((x - size) < 0) || ((y + size) > map.getSizeY()) || ((y - size) < 0))
        return (isBuildable);
    if (map.getElem(x, y)->getType() == 'T')
        isBuildable = true;
    if (size == 0) {
        return (isBuildable);
    }
    else if (size == 1) {
        if ((map.getElem(x-1, y)->getType() == 'T') && (map.getElem(x+1, y)->getType() == 'T')
        && (map.getElem(x, y-1)->getType() == 'T') && (map.getElem(x, y+1)->getType() == 'T'))
            isBuildable = true;
        else
            isBuildable = false;
    }
    else if (size < 0)
        isBuildable = false;
    return (isBuildable);
}

bool Game::canPlace(Tower &tower, int xPos, int yPos){
    //* detect if the tower can be placed at theses coords
    /*  for(int i = 0; i<= this->towerList.size(); i++){
          if(xPos >= towerList[i]->getPosition().x && xPos >= towerList[i]->getPosition().y && xPos < towerList[i]->getPosition().x + tower.getSize().x && yPos < towerList[i]->getPosition().y + tower.getSize().y){
              return false;
          }
      }*/
    return true;
}

void Game::drawInfoBox(sf::RenderWindow& window, const sf::Vector2f& rectSize, const std::string& textString, bool display) {
        sf::RectangleShape rectangle(rectSize);
        sf::Color colorRect(255, 255, 255, 150);
        rectangle.setFillColor(colorRect);
        rectangle.setPosition((window.getSize().x - rectSize.x) / 2.05f, (window.getSize().y - rectSize.y) / 2.4f);

        this->infoBoxDisplay.setString(textString);
        this->infoBoxDisplay.setCharacterSize(32);
        sf::Color colorText(0, 0, 0, 150);
        this->infoBoxDisplay.setFillColor(colorText);
       // this->infoBoxDisplay.setStyle(sf::Text::Bold);
        this->infoBoxDisplay.setOrigin(this->infoBoxDisplay.getLocalBounds().width / 2.f, this->infoBoxDisplay.getLocalBounds().height / 2.f);
        this->infoBoxDisplay.setPosition(rectangle.getPosition() + 0.5f * rectSize);

        window.draw(rectangle);
        window.draw(this->infoBoxDisplay);
        if (display == true)
            window.display();
}

bool Game::waveEnd(sf::RenderWindow& window){
    //* return true if the current wave is ended , ifnot return else
    if (this->enemiesLeft <= 0) {
        //* if all the ennemies from the current wave are dead == wave ended
        //* deactivate towers, increase wave number
        this->deactivateTowers();
        this->drawInfoBox(window, {400, 150}, "Wave cleared !", true);
        sf::sleep(sf::seconds(1.5f));
        this->enemyList.at(currentWaveNumber).clear();
    //    this->sfmlCoinAnimation.clear();
        this->currentWaveNumber++;
        return true;
    } else {
        //* if all the ennemies from the current wave aren't dead == wave not ended
        return false;
    }
}

bool Game::gameEnd(){
    //* return true if game is ended, ifnot false
    
    if (this->player->getLifeNumber() == 0){
        std::cout << "ending game" << std::endl;
        //* if player lost all his lifes = game lost
     //   this->deactivateTowers();
       // this->gameLost();
        return true;
    } else if (this->enemyList[this->enemyList.size()-1].size() == 0){
        std::cout << "ending level" << std::endl;
        //* if all enemies form the last wave are dead  = game won
       // this->deactivateTowers();
        //this->gameWon();
        return true;
    } else {
        return false;
    }
}

void Game::gameWon(){
    //* game won
    std::cout << "Game Won !!!" << std::endl;
    std::cout << "Total kills : " << this->player->getTotalKill() << std::endl;
}

void Game::gameLost(){
    //* game lost
    std::cout << "Game Lost !!!" << std::endl;
}

void Game::activateTowers(){
    //* Activate all towers
    if (this->towerList.empty())
        return;
    std::cout << "TDTowers activation" << std::endl;
    for(int i = 0; i < this->towerList.size(); i++ ){
        this->towerList[i]->run(this->currentWave);
    }
}

void Game::deactivateTowers(){
    //* deactivate all towers
    std::cout << "TDTowers deactivation" << std::endl;
    for(int i = 0; i< this->towerList.size(); i++){
        if (this->towerList[i]->isActivated()) {
            this->towerList[i]->deactivate();
            this->towerList[i]->join();
        }
    }
}

bool Game::enemyAtBase(){

    //* test if an enemy is at the base
    for(int i = 0; i<= this->enemyList[this->currentWaveNumber].size(); i++ ){
        //* if an enemy is at the base -> decrease life number and erase the enemy
        std::cout << "An enemy is a the base" << std::endl;
        if(this->enemyList[this->currentWaveNumber][i]->getPosX() == this->baseCoord.x && this->enemyList[this->currentWaveNumber][i]->getPosY() == this->baseCoord.y){
            this->player->looseLife();
            this->sfmlHud->setMessage("Prevent enemies from reaching your base to win the game");

            this->enemyList[this->currentWaveNumber].erase(std::remove(enemyList[this->currentWaveNumber].begin(), enemyList[this->currentWaveNumber].end(), enemyList[this->currentWaveNumber][i]), enemyList[this->currentWaveNumber].end());
            return true;
        }else{
            return false;
        }
    }
}

void Game::createTower(){
    //* Tower choice
    std::cout << "Enter the integer corresponding to the type of tower you want to build :" << std::endl;
    std::cout << "1/ Basic Tower" << std::endl;
    std::cout << "2/ Sniper Tower" << std::endl;
    std::cout << "3/ Anti Air Tower" << std::endl;
    std::cout << "4/ Splash Tower" << std::endl;
    std::cout << "5/ Slow Tower" << std::endl;
    std::cout << "6/ Attack Speed Tower" << std::endl;
    std::string towerType;
    std::getline(std::cin, towerType);
    Tower *newTower;
    switch(stoi(towerType)){
        case 1:
           // newTower = new Tower(this, 2, this->currentWave, this->cellSize);
            break;
        case 2:
          //  SniperTower newTower = new SniperTower(this);
            break;
        case 3:
            //AntiAirTower newTower = new AntiAirTower(this);
            break;
        case 4:
           // SplashTower newTower = new SplashTower(this);
            break;
        case 5:
            //SlowTower newTower = new SlowTower(this);
            break;
        case 6:
            //AttackSpeedTower newTower = new AttackSpeedTower(this, this->towerList);
            break;
        default:
            break;
    }
    if(canBuy(*newTower, 0)){
        //* test if the player has enough coin to buy the tower
        //* ask tower coord
        std::cout << "posX : " << std::endl;
        std::string newTowerPosX;
        std::getline(std::cin, newTowerPosX);
        std::cout << "posY : " << std::endl;
        std::string newTowerPosY;
        std::getline(std::cin, newTowerPosY);  
        if(canPlace(*newTower, stoi(newTowerPosX), stoi(newTowerPosY))){
            newTower->setPosition(stoi(newTowerPosX), stoi(newTowerPosY), this->cellSize);
            this->addCoins(newTower->getCost());
            
            this->towerList.push_back(newTower);
            newTower->run(this->currentWave);
            std::cout << "Tower succesfully created " << std::endl;
            std::cout << "coin number : " << this->player->getCoinNumber() << std::endl;
        }else{
            std::cout << "Coords not valid " << std::endl;
        }
    }else{
        delete newTower;
    }
}

bool Game::canBuy(Tower &tower, int level){
    //* test if the player has enough coin to buy the tower
    if(this->player->getCoinNumber() >= tower.getCost()){
        std::cout << "You have enough coins !" << std::endl;
        return true;
    }else{
        std::cout << "You don't have enough coins !" << std::endl;
        return false;
    }
}

void Game::addCoins(int number) {
    this->player->addCoin(number);
    std::cout << "You know have " << this->player->getCoinNumber() << " coins" << std::endl;
}

void Game::looseCoins(int number) {
    this->player->looseCoin(number);
    std::cout << "You know have " << this->player->getCoinNumber() << " coins" << std::endl;
}

void Game::startLevel(){
    std::cout << "Starting level ..." << std::endl;
    //* start level
    //*this->enemyList = retrieveLevel.getNextLevel();
}

void Game::setAllHoveringSprites(TDMap &map, sf::RenderWindow &window, int posX, int posY, bool showBuildable, Tower *towerInfos) {
    int radius = towerInfos->getSize() - 1;
    int range = towerInfos->getRange();
    if ((posX > this->mapMaxPosX) || (posY > this->mapMaxPosY))
        return;
    if (radius <= 1) {
        bool isBuildable = isBuildableAtPositionForSmaller(map, posX,
                                                           posY, radius);
        setHoveringSprites(window, posX, posY, range,
                           isBuildable, 48);
        setHoveringSprites(window, posX, posY, radius,
                           isBuildable, 128);
    }
    else {
        bool isBuildable = isBuildableAtPosition(map, posX, posY,
                                                 radius);
        setHoveringSprites(window, posX, posY, range,
                           isBuildable, 48 );
        setHoveringSprites(window, posX, posY, radius,
                           isBuildable, 128);

    }
    if (showBuildable)
        setHoveringBuildable(window, posX, posY, this->towerStoreList.at(this->towerSelectorIndex).at(0)->getTowerSpritePtr());
}

void Game::setHoveringSprites(sf::RenderWindow &window, int posX, int posY, int radius, bool isBuildable, int fade) {
    if ((posX > this->mapMaxPosX) || (posY > this->mapMaxPosY))
        return;
    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            if (i*i + j*j <= radius*radius) {
                sf::RectangleShape hoveringSprite(sf::Vector2f(this->cellSize - 3, this->cellSize - 3));
                if (isBuildable == false) {
                    sf::Color color(255, 0, 0, fade);
                    hoveringSprite.setFillColor(color);
                }
                else {
                    sf::Color color(0, 0, 255, fade);
                    hoveringSprite.setFillColor(color);
                }
                hoveringSprite.setPosition((posX + i) * this->cellSize + _GAME_POSITION_X +1.5, (posY + j) * this->cellSize + _GAME_POSITION_Y + 1.5);
                window.draw(hoveringSprite);
            }
        }
    }
}

bool Game::isOnPath(MapCell *cell) {
    if (cell->getType() == 'X')
        return (true);
    else
        return (false);
}

void Game::setHoveringBuildable(sf::RenderWindow &window, int posX, int posY, sf::Sprite *buildableSprite) {
    if ((posX > this->mapMaxPosX) || (posY > this->mapMaxPosY))
        return;
    buildableSprite->setPosition((posX) * this->cellSize + (this->cellSize / 2) + _GAME_POSITION_X, (posY) * this->cellSize + (this->cellSize / 2) + _GAME_POSITION_Y);
    window.draw(*buildableSprite);
}