//
// Created by adrie on 12/04/2023.
//

#ifndef UNTITLED1_MISSILELAUNCHER_HPP
#define UNTITLED1_MISSILELAUNCHER_HPP

#include "../TDUnits/TDUnit.hpp"
#include "../TDGraphics/SFMLMissileLoader.hpp"
#include "SFML/Graphics.hpp"
#include "../TDTowers/MissileThread.hpp"

class MissileLauncher {
private:
    int                              _cellSize;
    SFMLMissileLoader                &_sfmlMissileLoader;
    std::string                      _typeName;
    std::vector<MissileThread*>       _missiles;
public:
    MissileLauncher(SFMLMissileLoader &sfmlMissileLoader, int cellSize, std::string typeName);
    ~MissileLauncher();
    void endFinishedThreads();
    void shoot(int towerPosX, int towerPosY, TDUnit *target);
    int getTotalMissiles();
    sf::Sprite getSpriteByIndex(int index);
};

#endif //UNTITLED1_MISSILELAUNCHER_HPP
