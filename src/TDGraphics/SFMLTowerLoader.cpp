//
// Created by adrie on 06/04/2023.
//

#include <iostream>

#include "SFMLTowerLoader.hpp"

SFMLTowerLoader::SFMLTowerLoader() {
    if (!(this->_basic.loadFromFile("Sprites/MyTiles/turret_1_1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_speed.loadFromFile("Sprites/MyTiles/turret_02_mk1.png")))
        std::cout << "Error on loading texture..." << std::endl;
}

SFMLTowerLoader::~SFMLTowerLoader() {

}