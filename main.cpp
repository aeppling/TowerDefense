#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <mutex>

#include "SFMLLoader.hpp"
#include "mapParser.hpp"
#include "AStarPathFinding.hpp"
#include "TDUnit.hpp"
#include "RetrieveLevel.hpp"
#include "SizeRatioCalculator.hpp"

bool isInPathFound(int x, int y, std::vector<MapCell*> path) {
    int i = 0;
    while (i != path.size()) {
        if ((path[i]->getPosX() == x) && (path[i]->getPosY() == y))
            return true;
        i++;
    }
    return (false);
}

void displayDebugMap(std::vector<std::vector<MapCell>> *map, std::vector<MapCell*> path) {
    int x;
    int y = 0;

    while (y != map->size()) {
        x = 0;
        while (x != (*map)[y].size()) {
            if (isInPathFound((*map)[y][x].getPosX(), (*map)[y][x].getPosY(), path) == true)
                std::cout << "S ";
            else
                std::cout << (*map)[y][x].getType() << " ";
            x++;
        }
        std::cout << std::endl;
        y++;
    }
    std::cout << "END OF DEBUG DISPLAY" << std::endl << std::endl;

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

bool    testMap(std::string path, MapCell *baseCell, std::vector<MapCell*> &spawnCells) {
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

void runUnits(std::vector<std::vector<TDUnit*>> &enemyList, TDMap &map, unsigned int &basePosX, unsigned int &basePosY, unsigned int wave) {
     //TEST WITHOUT ENNEMYILST VECTOR
    /*Bats myUnit(1,1);
    Cowards myUnit2(20, 20);
    myUnit.searchPath(nmap, basePosX, basePosY); // set base coord while retrieving the map
    myUnit.run();
    myUnit2.searchPath(nmap, basePosX, basePosY);
    myUnit2.run();*/
    std::vector<std::vector<MapCell>> *nmap = map.getMapVector();
    int unitCount = 0;
    while (unitCount != enemyList.at(wave).size()) {
        enemyList.at(wave).at(unitCount)->searchPath(nmap, basePosX, basePosY);
        enemyList.at(wave).at(unitCount)->run();
        unitCount++;
    }
}

/* UNCOMMENT TO DEBUG PATH FINDING
 std::cout << "START CELL 1 x/y : " << (*nmap)[0][1].getPosX() << " : " << (*nmap)[0][1].getPosY() << std::endl;
 std::cout << "GOAL CELL 1 x/y : " << (*nmap)[10][10].getPosX() << " : " << (*nmap)[10][10].getPosY() << std::endl;
 AStarPathFinding pathFinder((*nmap), (*nmap)[0][1], (*nmap)[20][29]);
 std::vector<MapCell*> path = pathFinder.runPathFinding();
 int i = 0;
 while (i != path.size()) {
     std::cout << path[i]->getPosX() << " : " << path[i]->getPosY() << " | ";
     i++;
 }
 std::cout << std::endl;
 displayDebugMap((nmap), path);
 if (path.empty()) {
     std::cout << "NO PATH FOUND !!!" << std::endl;
 }
*/

void setUnitsTextures(SFMLLoader &sfmlLoader, std::vector<std::vector<TDUnit*>> &enemyList,
                      int winSizeX, int winSizeY, int mapSizeX, int mapSizeY) {
    int wave_count = 0;
    int unit_count = 0;

    while (wave_count != enemyList.size()) {
        while (unit_count != enemyList.at(wave_count).size()) {
            enemyList.at(wave_count).at(unit_count)->setSprite(sfmlLoader, winSizeX, winSizeY, mapSizeX, mapSizeY);
            unit_count++;
        }
        wave_count++;
    }
}

bool isBuildable() {
    // your implementation here
}

void setObstacleTest(TDMap &map, sf::RenderWindow &window) {
    mouseCoordinates mouseCoord = getMouseCellCoordinate(map, window);
    if (mouseCoord.posY >= 0 && mouseCoord.posY < map.getSizeY() && mouseCoord.posX >= 0 && mouseCoord.posX < map.getSizeX())
    {
        // Do something with the clicked cell
        std::cout << "Clicked on case x:" << map.getElem(mouseCoord.posX, mouseCoord.posY)->getPosX();
        std::cout << " y:" << map.getElem(mouseCoord.posX, mouseCoord.posY)->getPosY() << std::endl;
        map.getElem(mouseCoord.posX, mouseCoord.posY)->setType('W');
        // ...
    }
}

void runWindowLevelLoop(sf::RenderWindow &window, TDMap &map, MapCell *baseCell, std::vector<std::vector<TDUnit *>> &enemyList) {
    int cellSize = getCellSize(window.getSize().x, window.getSize().y, map.getSizeX(), map.getSizeY());
    // SETTING UP MOUSE POINTER
    window.setMouseCursorVisible(false);
    sf::Texture mousePointerTexture;
    mousePointerTexture.loadFromFile("Sprites/sand_tile.png");
    sf::Sprite mousePointer(mousePointerTexture);
    sf::IntRect textureRect(0, 0, cellSize - 3, cellSize - 3); // -3 to see border and debug
    mousePointer.setTextureRect(textureRect);
    // INITIALISE LOOP VARIABLES
    std::thread unitThread;
    bool isWaveClean = true;
    bool isBuilding = false;
    unsigned int wave = 0;
    while (window.isOpen()) {
        sf::Event event;
        window.clear(sf::Color::Black);
        // CHOOS
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
            if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                if (isBuilding == false)
                    isBuilding = true;
                else
                    isBuilding = false;
            }
            if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (isBuilding == true) {
                    setObstacleTest(std::ref(map), std::ref(window));
                }
            }
        }
        int s = 0;
        // DISPLAY MAP
        while (s != map.getTileMaxSprite()) {
            window.draw(map.getTileSprite(s));
            s++;
        }
        // RUN WAVE
        if (isWaveClean == true) {
            isWaveClean = false;
            unsigned int basePosX = baseCell->getPosX();
            unsigned int basePosY = baseCell->getPosY();
            unitThread = std::thread(runUnits, std::ref(enemyList), std::ref(map), std::ref(basePosX), std::ref(basePosY), std::ref(wave));
        }
        //DISPLAY BUILDING AREA (before enemies)
        if (isBuilding == true)
            std::cout << "doit";
        // DISPLAY ENEMIES
        s = 0;
        while (s != enemyList.at(wave).size()) {
            window.draw(enemyList.at(wave).at(s)->getSprite());
            s++;
        }
        // DISPLAY MOUSE
        mousePointer.setColor(sf::Color::Blue);
        sf::Vector2i mousePositionScreen = sf::Mouse::getPosition(window);
        mousePointer.setPosition(mousePositionScreen.x, mousePositionScreen.y);
        window.draw(mousePointer);
        window.display();
    }
    displayDebugMap2(map.getMapVector());
    window.setActive(false);
}

int main() {
   // RETRIEVE ENEMY LIST
   std::vector<std::vector<TDUnit*>> enemyList;
   RetrieveLevel retrieveLevel(1);
   enemyList = retrieveLevel.getNextLevel();
   if (enemyList.size() == 0) {
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
    // SETTING WINDOW AND MAP
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Window", sf::Style::Default);
    window.setActive(true);
    SFMLLoader sfmlLoader;
    // MAP TEXTURE ARE SET IN SFMLLOAD WHILE CREATING MAP
    TDMap map("mapfilePathFinding.txt", sfmlLoader, window.getSize().x, window.getSize().y);
    // NOW SETTING UP UNIT TEXTURES AND CELL SIZE
    setUnitsTextures(sfmlLoader, enemyList, window.getSize().x, window.getSize().y, map.getSizeX(), map.getSizeY());
    // WINDOW LOOP AND MOUSE SETUP
    runWindowLevelLoop(window, map, baseCell, enemyList);
    return (0);
}
