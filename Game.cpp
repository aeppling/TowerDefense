#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Game.hpp"
#include "SizeRatioCalculator.hpp"

Game::Game(int difficulty, int level){
    this->levelRetriever = new RetrieveLevel(level);
    this->difficulty = difficulty;
    this->baseCoord = {0,0};
    this->lifeNumber = 15/(difficulty);
    this->currentWaveNumber = 0;
    std::vector<MapCell> spawnCells;
    this->enemyList = this->levelRetriever->getNextLevel();
    this->coinNumber = 500-(difficulty*100);
    this->unitCount = 0;
    this->spawnCount = 0;
    this->towerSelectorIndex = 0;
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

void Game::setUnitsTextures(SFMLLoader &sfmlLoader, std::vector<std::vector<TDUnit*>> &enemyList,
                      int winSizeX, int winSizeY, int mapSizeX, int mapSizeY) {
    int wave_count = 0;
    int unit_count = 0;

    while (wave_count != enemyList.size()) {
        unit_count = 0;
        while (unit_count != enemyList.at(wave_count).size()) {
            enemyList.at(wave_count).at(unit_count)->setSprite(sfmlLoader, winSizeX, winSizeY, mapSizeX, mapSizeY);
            unit_count++;
        }
        wave_count++;
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

int Game::loop(SFMLLoader &sfmlLoader, sf::RenderWindow &window, MapCell *baseCell, TDMap &map){
            startLevel();
            bool isBuilding = false;
            int timeBetweenSpawn = 200;
            int cellSize = getCellSize(window.getSize().x, window.getSize().y, map.getSizeX(), map.getSizeY());
            // SETTING UP MOUSE POINTER
            window.setMouseCursorVisible(false);
            sf::Texture mousePointerTexture;
            mousePointerTexture.loadFromFile("Sprites/sand_tile.png");
            sf::Sprite mousePointer(mousePointerTexture);
            sf::IntRect textureRect(0, 0, cellSize - 3, cellSize - 3); // -3 to see border and debug
            mousePointer.setTextureRect(textureRect);
            bool closing = false;
            while((this->gameEnd() != true) && window.isOpen()) {  // RUN WHILE GAME IS NOT END OR WINDOW OPEN
                std::chrono::steady_clock::time_point waveChronoStart = std::chrono::steady_clock::now();
                std::cout << "Running units & towers..." << std::endl;
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
                Tower *buildTowerTest = new Tower(this, 1, this->currentWave);
                Tower *buildTowerTest2 = new Tower(this, 2, this->currentWave);
                Tower *buildTowerTest3 = new Tower(this, 3, this->currentWave);
                Tower *buildTowerTest4 = new Tower(this, 4, this->currentWave);
                this->towerStoreList.push_back(buildTowerTest);
                this->towerStoreList.push_back(buildTowerTest2);
                this->towerStoreList.push_back(buildTowerTest3);
                this->towerStoreList.push_back(buildTowerTest4);
                std::cout << "Tower initiate OK" << std::endl;
                // PROBLEM IS I RE-ASSIGN NEW TOURS ? BUT THE WORKING TOURS IS ON TOO
                std::cout << "Wave contain " << this->currentWave->size() << " ennemies" << std::endl;
                usleep(3000);
                while(!this->waveEnd()) { // RUN WHILE WAVE IS NOT FINISHED
                    isWaveRunning = true;
                    std::chrono::steady_clock::time_point testTime = std::chrono::steady_clock::now(); // SET CURRENT ELAPSED TIME ON WAVE
                    int waveChronoElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(testTime - waveChronoStart).count();
                    if ((waveChronoElapsed >= timeBetweenSpawn) && (this->unitCount != this->enemyList.at(this->currentWaveNumber).size())) { // RUN A UNIT IF ENOUGH TIME ELAPSED
                        unsigned int basePosX = baseCell->getPosX();
                        unsigned int basePosY = baseCell->getPosY();
                        runUnit(std::ref(this->enemyList), std::ref(map), std::ref(basePosX), std::ref(basePosY),
                                 std::ref(this->currentWaveNumber), this->spawnCells, this->unitCount, this->spawnCount);
                        this->spawnCount++;
                        this->unitCount++;
                        std::cout << "Mob Spawned" << std::endl;
                        if (this->spawnCount >= this->spawnCells.size())
                            this->spawnCount = 0;
                        waveChronoStart = std::chrono::steady_clock::now();
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
                        if (event.type == sf::Event::MouseButtonPressed &&
                            sf::Mouse::isButtonPressed(sf::Mouse::Right)) { // SWITCH BUILDING MODE ON/OFF
                            if (isBuilding == false) {
                                isBuilding = true;
                            }
                            else {
                                toBuild = nullptr;
                                isBuilding = false;
                            }
                        }
                        if (isBuilding == true) {
                            if (event.type == sf::Event::MouseButtonPressed &&
                                sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // BUILD CURRENT BUILDABLE
                                setObstacleTest(std::ref(map), std::ref(window), sfmlLoader);
                            }
                            if (event.type == sf::Event::KeyPressed) {
                                if (event.key.code == sf::Keyboard::Right) {
                                    if (this->towerStoreList.size() <= 1)
                                        break;
                                    if (this->towerSelectorIndex >= (this->towerStoreList.size() - 1))
                                        this->towerSelectorIndex = 0;
                                    else
                                        this->towerSelectorIndex++;
                                }
                                else if (event.key.code == sf::Keyboard::Left) {
                                    if (this->towerStoreList.size() <= 1)
                                        break;
                                    if (this->towerSelectorIndex == 0) {
                                        this->towerSelectorIndex = this->towerStoreList.size() - 1;
                                    }
                                    else
                                        this->towerSelectorIndex--;
                                }
                            }
                            if (event.type == sf::Event::KeyPressed &&
                                event.key.code == sf::Keyboard::T) { // TOWER BUILD TESTING -> SHOULD GO WITH WALL (UPPER IF) AFTER TEST OK
                                toBuild = this->towerStoreList.at(this->towerSelectorIndex);
                                setTowerTest(std::ref(map), std::ref(window), sfmlLoader, toBuild, isWaveRunning);
                                if (toBuild == nullptr)
                                    isBuilding = false;
                            }
                        }
                    }
                    if (closing == true)
                        break;
                    int s = 0;
                    // DISPLAY MAP
                    while (s != map.getTileMaxSpriteY()) {
                        int s2 = 0;
                        while (s2 != map.getTileMaxSpriteX(s)) {
                            window.draw(map.getTileSprite(s, s2));
                            s2++;
                        }
                        s++;
                    }
                    //DISPLAY BUILDING AREA (before enemies) and SHOOTING RANGE if tower building
                    if (isBuilding == true) {
                        mouseCoordinates mouseCoord = getMouseCellCoordinate(map, window);
                        int radius = this->towerStoreList.at(this->towerSelectorIndex)->getSize() - 1;
                        if (radius <= 1)
                            setHoveringSprites(window, mouseCoord.posX, mouseCoord.posY, radius, isBuildableAtPositionForSmaller(map, mouseCoord.posX, mouseCoord.posY, radius));
                        else
                            setHoveringSprites(window, mouseCoord.posX, mouseCoord.posY, radius, isBuildableAtPosition(map, mouseCoord.posX, mouseCoord.posY, radius));
                    }
                    // DISPLAY ENNEMIES
                    s = 0;
                    while (s != enemyList.at(this->currentWaveNumber).size()) {
                        window.draw(enemyList.at(this->currentWaveNumber).at(s)->getSprite());
                        s++;
                    }
                    // SET AND DISPLAY MOUSE
                    if (isBuilding == true)
                        mousePointer.setColor(sf::Color::Blue);
                    else
                        mousePointer.setColor(sf::Color::Cyan);
                    sf::Vector2i mousePositionScreen = sf::Mouse::getPosition(window);
                    mousePointer.setPosition(mousePositionScreen.x, mousePositionScreen.y);
                    window.draw(mousePointer);
                    window.display();
                }
                std::cout << "WAVE ENDED" << std::endl;
        }
}

int Game::launch(SFMLLoader &sfmlLoader, sf::RenderWindow &window) {
    // GAME INITIALISATON
    // RETRIEVE ENEMY LIST (in consrtuctor for first wave)
    if (this->enemyList.size() == 0) {
        std::cout << "Couldn't retrieve level informations, leaving..." << std::endl;
        return (-1);
    }
    // TESTING MAP VALIDITY AND RETRIEVING SPAWN CELLS
    MapCell *baseCell = new MapCell('B', -1, -1);
    std::vector<MapCell*> spawnCells;
    if (testMap("mapfilePathFinding.txt", baseCell, spawnCells) == false) {
        std::cout << "Cannot load level : Map is not valid." << std::endl;
        return (-1);
    }
    //UNCOMMENT TO DEBUG SPAWNS
    /* int i = 0;
     while (i < spawnCells.size()) {
         std::cout << "Spawn : x:" << spawnCells[i]->getPosX() << " y:" << spawnCells[i]->getPosY() << std::endl;
         i++;
     }*/
    this->spawnCells = spawnCells;
    std::cout << "Base : x:" << baseCell->getPosX() << " y:" << baseCell->getPosY() << std::endl;
    // MAP TEXTURE ARE SET IN SFMLLOAD WHILE CREATING MAP
    TDMap map("mapfilePathFinding.txt", sfmlLoader, window.getSize().x, window.getSize().y);
    // NOW SETTING UP UNIT TEXTURES AND CELL SIZE
    setUnitsTextures(sfmlLoader, this->enemyList, window.getSize().x, window.getSize().y, map.getSizeX(), map.getSizeY());
    this->cellSize = getCellSize(window.getSize().x, window.getSize().y, map.getSizeX(), map.getSizeY());
    this->loop(sfmlLoader, window, baseCell, map);
}

void Game::startWave(TDMap &map, MapCell *baseCell, std::vector<MapCell*> &spawnCells){
    //* start the wave
    std::cout << "Starting wave" << currentWaveNumber << "/" << this->enemyList.size() << std::endl;
    std::cout << "The wave contains " <<  this->currentWave->size() << " enemies" << std::endl;
    std::cout << "Life number : " << this->lifeNumber << std::endl;
    std::cout << "Coin number : " << this->coinNumber << std::endl;
    //* activate towers
    this->activateTowers();
    // NO THREAD HERE BUT COUNTER IN MAIN LOOP AND CALL EVERY x SECONDS
}

void Game::setTowerTest(TDMap &map, sf::RenderWindow &window, SFMLLoader sfmlLoader, Buildable *toBuild, bool isWaveRunning) {
    mouseCoordinates mouseCoord = getMouseCellCoordinate(map, window);
    if (mouseCoord.posY >= 0 && mouseCoord.posY < map.getSizeY() && mouseCoord.posX >= 0 && mouseCoord.posX < map.getSizeX()) {
        // SET TOWER
        if (map.getElem(mouseCoord.posX, mouseCoord.posY)->getType() == 'T') { // CHECK IF TOWER BUILDABLE CELL
            // CHECK IF ENOUGH SPACE TO BUILD
            // i should already have a function to do this because of hoverring mouse area
            if ((isBuildableAtPosition(map, mouseCoord.posX, mouseCoord.posY, toBuild->getSize() - 1) == true)
                || (toBuild->getSize() <= 1)) {
                // SET CURRENT CELL TO 'A' WITH OTHER CELL (FULL SIZE) (test if unit go through)
                std::cout << "Building" << std::endl;
                map.getElem(mouseCoord.posX, mouseCoord.posY)->setType('A');
                // BUILD->Add tower with its coordinate to vector of actives towers
                Tower *toAdd = dynamic_cast<Tower *>(toBuild);
                if (toAdd == nullptr) {
                    std::cout << "Dynamic cast failed from Buidlable to Tower" << std::endl;
                    return;
                }
                this->towerList.push_back(toAdd);
                this->towerList[this->towerList.size() - 1]->setPosition(mouseCoord.posX, mouseCoord.posY);
                toBuild = nullptr;
                if (isWaveRunning == true)
                    this->towerList[this->towerList.size() - 1]->run(this->currentWave);
                map.refreshTextures(sfmlLoader);
                this->towerStoreList.erase(this->towerStoreList.begin() + this->towerSelectorIndex);
            }
        }
    }
}

void Game::setObstacleTest(TDMap &map, sf::RenderWindow &window, SFMLLoader sfmlLoader) {
    mouseCoordinates mouseCoord = getMouseCellCoordinate(map, window);
    if (mouseCoord.posY >= 0 && mouseCoord.posY < map.getSizeY() && mouseCoord.posX >= 0 && mouseCoord.posX < map.getSizeX())
    {
        // SET WALL (WILL BE TOWER & WALL LATER)
        if (map.getElem(mouseCoord.posX, mouseCoord.posY)->getType() == 'X') {
            map.getElem(mouseCoord.posX, mouseCoord.posY)->setType('W');
        }
        else if (map.getElem(mouseCoord.posX, mouseCoord.posY)->getType() == 'W') {
            map.getElem(mouseCoord.posX, mouseCoord.posY)->setType('X');
        }
        map.refreshTextures(sfmlLoader);
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

bool Game::waveEnd(){
    //* return true if the current wave is ended , ifnot return else
    if (this->currentWave->size() == 0) {
        //* if all the ennemies from the current wave are dead == wave ended
        //* deactivate towers, increase wave number
        this->deactivateTowers();
        this->currentWaveNumber++;
        return true;
    } else {
        //* if all the ennemies from the current wave aren't dead == wave not ended
        return false;
    }
}

bool Game::gameEnd(){
    //* return true if game is ended, ifnot false
    
    if(this->lifeNumber == 0){
        std::cout << "ending game" << std::endl;
        //* if player lost all his lifes = game lost
     //   this->deactivateTowers();
       // this->gameLost();
        return true;
    }else if(this->enemyList[this->enemyList.size()-1].size() == 0){
        std::cout << "ending level" << std::endl;
        //* if all enemies form the last wave are dead  = game won
       // this->deactivateTowers();
        //this->gameWon();
        return true;
    }else{
        return false;
    }
}

void Game::gameWon(){
    //* game won
    std::cout << "Game Won !!!" << std::endl;    
}

void Game::gameLost(){
    //* game lost
    std::cout << "Game Lost !!!" << std::endl;
}

void Game::activateTowers(){
    //* Activate all towers
    if (this->towerList.empty())
        return;
    std::cout << "Towers activation" << std::endl;
    for(int i = 0; i < this->towerList.size(); i++ ){
        this->towerList[i]->run(this->currentWave);
    }
}

void Game::deactivateTowers(){
    //* deactivate all towers
    std::cout << "Towers deactivation" << std::endl;
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
            this->lifeNumber--;
            std::cout << "life number :" << this->lifeNumber << std::endl;
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
            newTower = new Tower(this, 2, this->currentWave);
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
            newTower->setPosition(stoi(newTowerPosX), stoi(newTowerPosY));
            this->addCoins(0-newTower->getCost(0));
            this->towerList.push_back(newTower);
            newTower->run(this->currentWave);
            std::cout << "Tower succesfully created " << std::endl;
            std::cout << "coin number : " << this->coinNumber << std::endl;
        }else{
            std::cout << "Coords not valid " << std::endl;
        }
    }else{
        delete newTower;
    }
}

bool Game::canBuy(Tower &tower, int level){
    //* test if the player has enough coin to buy the tower
    if(this->coinNumber >= tower.getCost(level)){
        std::cout << "You have enough coins !" << std::endl;
        return true;
    }else{
        std::cout << "You don't have enough coins !" << std::endl;
        return false;
    }
}

void Game::addCoins(int number){
    this->coinNumber+= number;
    std::cout << "You know have " << this->coinNumber << " coins" << std::endl;
}

void Game::upgradeTower(Tower &tower){
    if(!tower.isMaxed()){
        if(canBuy(tower, tower.getLevel() + 1)){
            this->addCoins(0-tower.getCost(tower.getLevel() + 1));
            tower.upgrade();      
        }
    }
}

void Game::startLevel(){
    std::cout << "Starting level ..." << std::endl;
    //* start level
    //*this->enemyList = retrieveLevel.getNextLevel();
}

void Game::setHoveringSprites(sf::RenderWindow &window, int posX, int posY, int radius, bool isBuildable) {
    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            if (i*i + j*j <= radius*radius) {
                sf::RectangleShape hoveringSprite(sf::Vector2f(this->cellSize - 3, this->cellSize - 3));
                if (isBuildable == false)
                    hoveringSprite.setFillColor(sf::Color::Red);
                else
                    hoveringSprite.setFillColor(sf::Color::Blue);
                hoveringSprite.setPosition((posX + i) * this->cellSize, (posY + j) * this->cellSize);
                window.draw(hoveringSprite);
            }
        }
    }
}