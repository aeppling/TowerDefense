//
// Created by adrie on 06/04/2023.
//

#include <iostream>

#include "SFMLTowerLoader.hpp"

SFMLTowerLoader::SFMLTowerLoader() {
    if (!(this->_basic.loadFromFile("Sprites/MyTiles/basic_tower.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_speed.loadFromFile("Sprites/MyTiles/speed_tower.png")))
        std::cout << "Error on loading texture..." << std::endl;
}

SFMLTowerLoader::~SFMLTowerLoader() {

}