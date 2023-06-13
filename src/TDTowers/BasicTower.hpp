//
// Created by adrie on 11/04/2023.
//

#ifndef UNTITLED1_BASICTOWER_HPP
#define UNTITLED1_BASICTOWER_HPP

#include "Tower.hpp"

class BasicTower : public Tower {

public :
    BasicTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlLoaderTower, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, SFTowerSoundLoader &soundLoader);

};

#endif //UNTITLED1_BASICTOWER_HPP
