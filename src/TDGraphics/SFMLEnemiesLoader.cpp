//
// Created by adrie on 06/04/2023.
//

#include <iostream>

#include "SFMLEnemiesLoader.hpp"

SFMLEnemiesLoader::SFMLEnemiesLoader() {
    if (!(this->_drone.loadFromFile("Sprites/Units/CharRed1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_missile.loadFromFile("Sprites/Units/Missile_C_Large.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_alien.loadFromFile("Sprites/Units/Enemy_2_B_Large.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_spaceship.loadFromFile("Sprites/Units/Ship_2_C_Large.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_flyingDrone.loadFromFile("Sprites/Units/FlyingDrone.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_regenerateDrone.loadFromFile("Sprites/Units/RegenerateDrone.png")))
        std::cout << "Error on loading texture..." << std::endl;
    //this->_pathCell.setSmooth(false);
    //this->_notWalkableCell.setSmooth(false);
    //   this->_wallCell.loadFromFile();
    // this->_mapBorder.loadFromFile();
}

SFMLEnemiesLoader::~SFMLEnemiesLoader() {

}