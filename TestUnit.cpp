//
// Created by adrie on 17/03/2023.
//

#include <iostream>
#include "TestUnit.hpp"

TestUnit::TestUnit(int posX, int posY) : _posX(posX), _posY(posY) {
    this->_speed = 500;
    this->_timeOfLastMove = std::chrono::steady_clock::now();
}

TestUnit::~TestUnit() {}

void    TestUnit::live() {
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

void    TestUnit::move() {
    MapCell *nextTo = this->_path.at(0);
    this->_posX = nextTo->getPosX();
    this->_posY = nextTo->getPosY();
    this->_path.erase(this->_path.begin());
}

void    TestUnit::searchPath(std::vector<std::vector<MapCell>> *nmap, int baseCoordX, int baseCoordY) {
    AStarPathFinding pathFinder((*nmap), (*nmap)[this->_posY][this->_posX], (*nmap)[baseCoordY][baseCoordX]);
    // HERE I NEED TO REPLACE DEST COORD BY NEAREST BASE
    this->_path = pathFinder.runPathFinding();
}

void    TestUnit::setPath(std::vector<MapCell*> path) {
    this->_path = path;
}

bool    TestUnit::isAtBase() {
    if (this->_path.size() > 0) {
        return (false);
    }
    else
        return (true);
}