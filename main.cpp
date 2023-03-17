#include <iostream>

#include "mapParser.hpp"
#include "AStarPathFinding.hpp"
#include "TestUnit.hpp"

bool isInPathFound(int x, int y, std::vector<MapCell*> path) {
    int i = 0;
    while (i != path.size()) {
        if ((path[i]->getPosX() == x) && (path[i]->getPosY() == y))
            return true;
        i++;
    }
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
    TDMap map("../mapfilePathFinding.txt");
    TestUnit myUnit(1,1);
    TestUnit myUnit2(20, 20);
    std::vector<std::vector<MapCell>> *nmap = map.getMapVector();
    myUnit.searchPath(nmap, 29, 20); // set base coord while retrieving the map
    myUnit.live();
    myUnit2.searchPath(nmap, 3, 1);
    myUnit2.live();
    return 0;
}
