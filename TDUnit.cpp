//
// Created by adrie on 17/03/2023.
//

#include <iostream>
#include "TDUnit.hpp"

void    TDUnit::live() {
    while (!(this->isAtBase())) {
        std::chrono::steady_clock::time_point testTime = std::chrono::steady_clock::now();
        int res = std::chrono::duration_cast<std::chrono::milliseconds>(testTime - this->_timeOfLastMove).count();
        if (res >= this->_speed) {
            if (!(this->isAtBase())) {
                std::cout << "Move now " << '[' + this->getTypeName() + "] :" << " Current pos x:" << this->_posX << " y:" << this->_posY
                          << std::endl;
                this->move();
                this->_timeOfLastMove = std::chrono::steady_clock::now();
            }
        }
    }
    std::cout << this->getTypeName() << " has arrived" << std::endl;
}

void    TDUnit::run() {
    //UNCOMMENT TO DEBUG PATH
 /*   int i = 0;
    std::cout << "Path of " << this->getTypeName() << std::endl;
    while (i < this->_path.size()) {
        std::cout << "x:" << this->_path[i]->getPosX() << " y:" << this->_path[i]->getPosY() << std::endl;
        i++;
    }*/
    this->_thread = std::thread(&TDUnit::live, this);
}

void    TDUnit::move() {
    std::shared_ptr<MapCell> nextTo = this->_path[0];
 //   std::cout << "next pos : " << nextTo->getPosX() << ":" << nextTo->getPosY() << std::endl;
    this->_posX = nextTo->getPosX();
    this->_posY = nextTo->getPosY();
    this->_path.erase(this->_path.begin());
}

void    TDUnit::searchPath(std::vector<std::vector<MapCell>> *nmap, int baseCoordX, int baseCoordY) {
/*  std::vector<std::vector<MapCell>> uniqueMap;
    int x = 0;
    while (x != (*nmap).size()) {
        int y = 0;
        std::vector<MapCell> newLine;
        while (y != (*nmap)[x].size()) {
            MapCell copyCell((*nmap)[x][y]);
            newLine.push_back(copyCell);
            y++;
        }
        uniqueMap.push_back(newLine);
        x++;
    }*/
    AStarPathFinding pathFinder((*nmap), (*nmap)[this->_posY][this->_posX], (*nmap)[baseCoordY][baseCoordX]);
 //   std::cout << "DEBUUUG1" << std::endl;
    //AStarPathFinding pathFinder(uniqueMap, uniqueMap[this->_posY][this->_posX], uniqueMap[baseCoordY][baseCoordX]);
  //  std::cout << "DEBUUUG2" << std::endl;
    // HERE I NEED TO REPLACE DEST COORD BY NEAREST BASE
    pathFinder.runPathFinding(this->_path);
    //this->_path = pathFinder.runPathFinding();
    // PATH NO LONGER EXIST AFTER THIS???!!!
}

void    TDUnit::setSprite(SFMLLoader sfmlLoader, int winSizeX, int winSizeY, TDMap map) {
    // GET SIZE RATIO OF UNITS SPRITE FROM WINDOW AND MAP
   /* int smallerWinSize = std::min(winSizeX, winSizeY);
    int largerMapSize = std::max(this->_map.size(), this->_map[0].size());
    int cellSize = std::min(smallerWinSize / largerMapSize, smallerWinSize / largerMapSize);

    if ((this->_map.size() > 30) || (this->_map[0].size() > 30))
        cellSize = cellSize / 1.1;
    if ((this->_map.size() > 40) || (this->_map[0].size() > 40))
        cellSize = cellSize / 1.2;
    if ((this->_map.size() > 60) || (this->_map[0].size() > 60))
        cellSize = cellSize / 1.3;*/
    /*sf::Sprite newSprite;
    newSprite.setTexture(sfmlLoader.getPathCell());
    newSprite.setColor(sf::Color::Yellow);
    sf::IntRect textureRect(0, 0, cellSize - 3, cellSize - 3); // -3 to see border and debug
    newSprite.setTextureRect(textureRect);
    newSprite.setPosition(this->_map.at(y).at(x).getPosX() * cellSize, this->_map.at(y).at(x).getPosY() * cellSize);
    this->_sprite = newSprite;*/
}

bool    TDUnit::isAtBase() {
    if (this->_path.size() > 0) {
        return (false);
    }
    else
        return (true);
}