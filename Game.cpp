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
              unsigned int &basePosY, unsigned int wave, std::vector<MapCell*> &spawnCells, int unitCount) {
    // RUN EVERY UNIT THREADS
    // RUN THIS AS A THREAD ? SO I CAN DELAY EVERY SPAWNING
    std::vector<std::vector<MapCell>> *nmap = map.getMapVector();
    enemyList.at(wave).at(unitCount)->searchPath(nmap, basePosX, basePosY);
    enemyList.at(wave).at(unitCount)->run(&map);
    unitCount++;
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
    int i = 0;
    while (i < spawnCells.size()) {
        std::cout << "Spawn : x:" << spawnCells[i]->getPosX() << " y:" << spawnCells[i]->getPosY() << std::endl;
        i++;
    }
    std::cout << "Base : x:" << baseCell->getPosX() << " y:" << baseCell->getPosY() << std::endl;
    // MAP TEXTURE ARE SET IN SFMLLOAD WHILE CREATING MAP
    TDMap map("mapfilePathFinding.txt", sfmlLoader, window.getSize().x, window.getSize().y);
    // NOW SETTING UP UNIT TEXTURES AND CELL SIZE
    setUnitsTextures(sfmlLoader, this->enemyList, window.getSize().x, window.getSize().y, map.getSizeX(), map.getSizeY());
    this->loop(sfmlLoader, window, spawnCells, baseCell, map);
}

int Game::loop(SFMLLoader &sfmlLoader, sf::RenderWindow &window, std::vector<MapCell*> spawnCells,
               MapCell *baseCell, TDMap &map){
            startLevel();
            bool isBuilding = false;
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
                this->startWave(map, baseCell, spawnCells); // RUN UNITS & TOWERS
                int unitCount = 0; // UNIT PER WAVE COUNTER
                while(!this->waveEnd()) { // RUN WHILE WAVE IS NOT FINISHED
                    std::chrono::steady_clock::time_point testTime = std::chrono::steady_clock::now(); // SET CURRENT ELAPSED TIME ON WAVE
                    int waveChronoElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(testTime - waveChronoStart).count();
                    if ((waveChronoElapsed >= 1000) && (unitCount != this->enemyList.at(this->currentWaveNumber).size())) { // RUN A UNIT IF ENOUGH TIME ELAPSED
                        unsigned int basePosX = baseCell->getPosX();
                        unsigned int basePosY = baseCell->getPosY();
                        std::cout << "Run unit" << std::endl;
                        runUnit(std::ref(this->enemyList), std::ref(map), std::ref(basePosX), std::ref(basePosY),
                                 std::ref(this->currentWaveNumber), spawnCells, unitCount);
                        unitCount++;
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
                            sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                            if (isBuilding == false)
                                isBuilding = true;
                            else
                                isBuilding = false;
                        }
                        if (event.type == sf::Event::MouseButtonPressed &&
                            sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            if (isBuilding == true)
                                setObstacleTest(std::ref(map), std::ref(window), sfmlLoader);
                        }
                    }
                    if (closing == true)
                        break;
                    //DISPLAY BUILDING AREA (before enemies) and SHOOTING RANGE if tower building
                    if (isBuilding == true) {
                    }
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
        }
}

void Game::startWave(TDMap &map, MapCell *baseCell, std::vector<MapCell*> &spawnCells){
    //* start the wave
    std::cout << "Starting wave" << currentWaveNumber << "/" << this->enemyList.size() << std::endl;
    std::cout << "The wave contains " <<  this->enemyList[this->currentWaveNumber].size() << " enemies" << std::endl;
    std::cout << "Life number : " << this->lifeNumber << std::endl;
    std::cout << "Coin number : " << this->coinNumber << std::endl;
    //* activate towers
    this->activateTowers();
    // NO THREAD HERE BUT COUNTER IN MAIN LOOP AND CALL EVERY x SECONDS
}

void Game::setObstacleTest(TDMap &map, sf::RenderWindow &window, SFMLLoader sfmlLoader) {
    mouseCoordinates mouseCoord = getMouseCellCoordinate(map, window);
    if (mouseCoord.posY >= 0 && mouseCoord.posY < map.getSizeY() && mouseCoord.posX >= 0 && mouseCoord.posX < map.getSizeX())
    {
        // Do something with the clicked cell
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

bool Game::waveEnd(){
    //* return true if the current wave is ended , ifnot return else
    if (this->enemyList[this->currentWaveNumber].size() == 0) {
        //* if all the ennemies from the current wave are dead == wave ended
        std::cout << "wave ended" << std::endl;
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
    std::cout << "Tower activation" << std::endl;
    for(int i = 0; i<= this->towerList.size(); i++ ){
        this->towerList[i]->run(this->enemyList[this->currentWaveNumber]);
    }
}

void Game::deactivateTowers(){
    //* deactivate all towers
    std::cout << "Tower deactivation" << std::endl;
    for(int i = 0; i<= this->towerList.size(); i++ ){
        this->towerList[i]->deactivate();
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
            newTower = new Tower(this);
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
            newTower->run(this->enemyList[this->currentWaveNumber]);
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

bool Game::canPlace(Tower &tower, int xPos, int yPos){
    //* detect if the tower can be placed at theses coords
    for(int i = 0; i<= this->towerList.size(); i++){
        if(xPos >= towerList[i]->getPosition().x && xPos >= towerList[i]->getPosition().y && xPos < towerList[i]->getPosition().x + tower.getSize().x && yPos < towerList[i]->getPosition().y + tower.getSize().y){
            return false;
        }
    }
    return true;
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