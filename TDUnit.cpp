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
                std::cout << "Move now : " << res << " Current pos x:" << this->_posX << " y:" << this->_posY
                          << std::endl;
                this->move();
                this->_timeOfLastMove = std::chrono::steady_clock::now();
            }
        }
    }
    std::cout << "Unit has arrived" << std::endl;
}

void    TDUnit::run() {
    this->_thread = std::thread(&TDUnit::live, this);
}

void    TDUnit::move() {
   // MapCell *nextTo = this->_path.at(0);
    //std::cout << "next pos : " << nextTo->getPosX() << ":" << nextTo->getPosY() << std::endl;
    this->_posX = this->_path.at(0)->getPosX();
    this->_posY = this->_path.at(0)->getPosY();
    this->_path.erase(this->_path.begin());
}

void    TDUnit::searchPath(std::vector<std::vector<MapCell>> *nmap, int baseCoordX, int baseCoordY) {
    //std::vector<std::vector<MapCell>> uniqueMap;

    AStarPathFinding pathFinder((*nmap), (*nmap)[this->_posY][this->_posX], (*nmap)[baseCoordY][baseCoordX]);
    // HERE I NEED TO REPLACE DEST COORD BY NEAREST BASE
    this->_path = pathFinder.runPathFinding();

    int i = 0;
    std::cout << "Path of " << this->getTypeName() << std::endl;
    while (i < this->_path.size()) {
        std::cout << "x:" << this->_path[i]->getPosX() << " y:" << this->_path[i]->getPosY() << std::endl;
        i++;
    }
}

void    TDUnit::setPath(std::vector<MapCell*> path) {
    this->_path = path;
}

bool    TDUnit::isAtBase() {
    if (this->_path.size() > 0) {
        return (false);
    }
    else
        return (true);
}