//
// Created by adrie on 12/04/2023.
//

#include "MissileLauncher.hpp"
#include "MissileThread.hpp"

MissileLauncher::MissileLauncher(SFMLMissileLoader &sfmlMissileLoader, int cellSize, std::string typeName)
                                : _sfmlMissileLoader(sfmlMissileLoader), _cellSize(cellSize), _typeName(typeName) {
}

void MissileLauncher::shoot(int towerPosX, int towerPosY, TDUnit *target) {
    //shootMissile(this->_sfmlMissileLoader, {(float)towerPosX, (float)towerPosY},target->getSprite().getPosition(), this->_cellSize, 200);

}