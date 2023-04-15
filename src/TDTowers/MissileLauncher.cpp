//
// Created by adrie on 12/04/2023.
//

#include "MissileLauncher.hpp"
#include "MissileThread.hpp"

MissileLauncher::MissileLauncher(SFMLMissileLoader &sfmlMissileLoader, int cellSize, std::string typeName)
                                : _sfmlMissileLoader(sfmlMissileLoader), _cellSize(cellSize), _typeName(typeName) {
}

void MissileLauncher::shoot(int towerPosX, int towerPosY, TDUnit *target) {
    this->_missiles.push_back(new MissileThread);
    this->_missiles.at(this->_missiles.size() - 1)->startThread(this->_sfmlMissileLoader, {(float)towerPosX, (float)towerPosY},target->getSprite().getPosition(), this->_cellSize, 5, this->_typeName);
}

void MissileLauncher::endFinishedThreads() {
    int i = 0;
    while (i < this->_missiles.size()) {
        if (this->_missiles.at(i)->isArrived()) {
                this->_missiles.erase(this->_missiles.begin() + i);
        }
        i++;
    }
}

int MissileLauncher::getTotalMissiles() {
    return (this->_missiles.size());
}

sf::Sprite MissileLauncher::getSpriteByIndex(int index) {
    return (this->_missiles.at(index)->getSprite());
}