#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <mutex>

#include "SFMLLoader.hpp"
#include "mapParser.hpp"
#include "AStarPathFinding.hpp"
#include "TDUnit.hpp"
#include "RetrieveLevel.hpp"

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

    while (y != map->size()) {
        x = 0;
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
    TDMap map("mapfilePathFinding.txt", sfmlLoader, window.getSize().x, window.getSize().y);
    // WINDOW LOOP IN THREAD
    std::thread unitThread;
    bool isWaveClean = true;
    unsigned int wave = 0;
    while (window.isOpen()) {
        sf::Event event;
        window.clear(sf::Color::Black);
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                    // Handle other events here
            }
        }
        int s = 0;
        while (s != map.getTileMaxSprite()) {
            window.draw(map.getTileSprite(s));
            s++;
        }
        if (isWaveClean == true) {
            isWaveClean = false;
            unsigned int basePosX = baseCell->getPosX();
            unsigned int basePosY = baseCell->getPosY();
            unitThread = std::thread(runUnits, std::ref(enemyList), std::ref(map), std::ref(basePosX), std::ref(basePosY), std::ref(wave));
        }
        s = 0;
        while (s != enemyList.at(wave).size()) {
            //window.draw(enemyList.at(wave).at(s)->getTypeName());
            s++;
        }
        // Update the game state
        // Draw the game
        // etc.
        window.display();
    }
    window.setActive(false);
    return (0);
}
