//
// Created by adrie on 17/03/2023.
//

#include <iostream>
#include "TDUnit.hpp"
#include "SizeRatioCalculator.hpp"

void    TDUnit::live() {
    while (!(this->isAtBase())) {
        std::chrono::steady_clock::time_point testTime = std::chrono::steady_clock::now();
        int res = std::chrono::duration_cast<std::chrono::milliseconds>(testTime - this->_timeOfLastMove).count();
        if (res >= this->_speed) {
            if (!(this->isAtBase())) {
               //std::cout << "Move now " << '[' + this->getTypeName() + "] :" << " Current pos x:" << this->_posX << " y:" << this->_posY
                 //          << std::endl;
                this->move();
                this->_timeOfLastMove = std::chrono::steady_clock::now();
            }
        }
    }
    std::cout << this->getTypeName() << " has arrived" << std::endl;
}

void    TDUnit::run(TDMap *map) {
    //UNCOMMENT TO DEBUG PATH
    this->_mapCopy = map;
    this->_thread = std::thread(&TDUnit::live, this);
}

void    TDUnit::move() {
    std::shared_ptr<MapCell> nextTo = this->_path[0];
    if (isBlocked(nextTo->getPosX(), nextTo->getPosY())) {
        this->_path.clear();
        this->searchPath(this->_mapCopy->getMapVector(), this->_baseCoordX, this->_baseCoordY);
        this->move();
       //nextTo = this->_path[0];
    }
    this->_posX = nextTo->getPosX();
    this->_posY = nextTo->getPosY();
    this->_sprite.setPosition(this->_posX * this->_unitSize, this->_posY * this->_unitSize);
  //  this->_sprite.move(;)
    this->_path.erase(this->_path.begin());
}

//benjamin.labastille@

void    TDUnit::searchPath(std::vector<std::vector<MapCell>> *nmap, int baseCoordX, int baseCoordY) {
    this->_baseCoordX = baseCoordX;
    this->_baseCoordY = baseCoordY;
    AStarPathFinding pathFinder((*nmap), (*nmap)[this->_posY][this->_posX], (*nmap)[baseCoordY][baseCoordX]);
    pathFinder.runPathFinding(this->_path);
}

void    TDUnit::setSprite(SFMLLoader &sfmlLoader, int winSizeX, int winSizeY, int mapSizeX, int mapSizeY) {
    // GET SIZE RATIO OF UNITS SPRITE FROM WINDOW AND MAP
    this->_unitSize = getCellSize(winSizeX, winSizeY, mapSizeX, mapSizeY);
    sf::Sprite newSprite;
    newSprite.setTexture(sfmlLoader.getCowards());
    newSprite.setColor(sf::Color::White);
    sf::IntRect textureRect(0, 0, this->_unitSize - 3, this->_unitSize - 3); // -3 to see border and debug
    newSprite.setTextureRect(textureRect);
    newSprite.setPosition(this->_posX * this->_unitSize, this->_posY * this->_unitSize);
    this->_sprite = newSprite;
}

bool    TDUnit::isAtBase() {
    if (this->_path.size() > 0) {
        return (false);
    }
    else
        return (true);
}

bool    TDUnit::isBlocked(int nextPosX, int nextPosY) {
    if (this->_mapCopy->getElem(nextPosX, nextPosY)->isWalkable() == false)
        return (true);
    else
        return (false);
}