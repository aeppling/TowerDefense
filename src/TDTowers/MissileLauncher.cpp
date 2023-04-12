//
// Created by adrie on 12/04/2023.
//

#include "MissileLauncher.hpp"
#include "MissileThread.hpp"

MissileLauncher::MissileLauncher(SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, int cellSize, std::string typeName)
                                : _sfmlMissileLoader(sfmlMissileLoader), _window(window), _cellSize(cellSize), _typeName(typeName) {
}

void MissileLauncher::shoot(int towerPosX, int towerPosY, TDUnit *target) {
    shootMissile(this->_sfmlMissileLoader, this->_window, {(float)towerPosX, (float)towerPosY},target->getSprite().getPosition(), this->_cellSize, 200);
}