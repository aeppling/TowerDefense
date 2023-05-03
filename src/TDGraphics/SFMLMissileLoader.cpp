//
// Created by adrie on 12/04/2023.
//

#include <iostream>
#include "SFMLMissileLoader.hpp"

SFMLMissileLoader::SFMLMissileLoader() {
    if (!(this->_basic.loadFromFile("Sprites/Missiles/01.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_speed.loadFromFile("Sprites/Missiles/23.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_antiAir.loadFromFile("Sprites/Missiles/48.png")))
        std::cout << "Error on loading texture..." << std::endl;
}

SFMLMissileLoader::~SFMLMissileLoader() {

}