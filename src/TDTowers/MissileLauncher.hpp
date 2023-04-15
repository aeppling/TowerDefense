//
// Created by adrie on 12/04/2023.
//

#ifndef UNTITLED1_MISSILELAUNCHER_HPP
#define UNTITLED1_MISSILELAUNCHER_HPP

#include "../TDUnits/TDUnit.hpp"
#include "../TDGraphics/SFMLMissileLoader.hpp"
#include "SFML/Graphics.hpp"

class MissileLauncher {
private:
    int                 _cellSize;
    SFMLMissileLoader   &_sfmlMissileLoader;
    std::string         _typeName;
    //std::vector<>       _missiles;
public:
    MissileLauncher(SFMLMissileLoader &sfmlMissileLoader, int cellSize, std::string typeName);
    ~MissileLauncher();
    void shoot(int towerPosX, int towerPosY, TDUnit *target);
};

#endif //UNTITLED1_MISSILELAUNCHER_HPP
