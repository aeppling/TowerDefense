//
// Created by adrie on 12/04/2023.
//

#include <iostream>
#include "SFMLMissileLoader.hpp"

SFMLMissileLoader::SFMLMissileLoader() {
    if (!(this->_basic.loadFromFile("ressources/Sprites/Missiles/11.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_speed.loadFromFile("ressources/Sprites/Missiles/23.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_antiAir.loadFromFile("ressources/Sprites/Missiles/48.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_slow.loadFromFile("ressources/Sprites/Missiles/34.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_sniper.loadFromFile("ressources/Sprites/Missiles/55.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_splash.loadFromFile("ressources/Sprites/Missiles/01.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_explosion1.loadFromFile("ressources/Sprites/MyTiles/bk_explo_one.png")))
        std::cout << "Error on loading texture..." << std::endl;
}

SFMLMissileLoader::~SFMLMissileLoader() {

}