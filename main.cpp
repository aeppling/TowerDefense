#include <stdlib.h>
#include <iostream>
#include <unistd.h>

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

int main() {

   /*
    std::vector<std::vector<MapCell>> *nmap = map.getMapVector();
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
   std::vector<std::vector<TDUnit*>> enemyList;
   RetrieveLevel retrieveLevel(1);
   enemyList = retrieveLevel.getNextLevel();
   if (enemyList.size() == 0) {
       std::cout << "Couldn't retrieve level informations, leaving..." << std::endl;
       return (-1);
   }
   // UNCOMMENT TO DEBUG WAVES RETRIEVE
  /* int x = 0;
   while (x != enemyList.size()) {
       std::cout << "Wave " << x + 1 << " :" << std::endl;
       int w = 0;
       while (w != enemyList[x].size()) {
           std::cout << enemyList[x][w]->getTypeName() << std::endl;
           w++;
       }
       std::cout << std::endl;
       x++;
   }
*/
   MapCell *baseCell = new MapCell('B', -1, -1);
   std::vector<MapCell*> spawnCells;
    if (testMap("../mapfilePathFinding.txt", baseCell, spawnCells) == false) {
        std::cout << "Cannot load level : Map is not valid." << std::endl;
        return (-1);
    }
    int i = 0;
    while (i < spawnCells.size()) {
        std::cout << "Spawn : x:" << spawnCells[i]->getPosX() << " y:" << spawnCells[i]->getPosY() << std::endl;
        i++;
    }
    std::cout << "Base : x:" << baseCell->getPosX() << " y:" << baseCell->getPosY() << std::endl;
    TDMap map("../mapfilePathFinding.txt");
    Bats myUnit(1,1);
    Cowards myUnit2(20, 20);
    std::vector<std::vector<MapCell>> *nmap = map.getMapVector();
    // COPY MAP VECTOR INSIDE SEARCH PATH ?
    myUnit.searchPath(nmap, baseCell->getPosX(), baseCell->getPosY()); // set base coord while retrieving the map
    myUnit.run();
    sleep(2);
    myUnit2.searchPath(nmap, baseCell->getPosY(), baseCell->getPosY());
    myUnit2.run();
    //displayDebugMap2((nmap));
    return (0);
}
