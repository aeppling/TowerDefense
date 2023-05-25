//
// Created by adrie on 06/04/2023.
//

#include <iostream>

#include "SFMLEnemiesLoader.hpp"

SFMLEnemiesLoader::SFMLEnemiesLoader() {
    if (!(this->_drone.loadFromFile("ressources/Sprites/Units/CharRed1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_missile.loadFromFile("ressources/Sprites/Units/Missile_C_Large.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_alien.loadFromFile("ressources/Sprites/Units/Enemy_2_B_Large.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_spaceship.loadFromFile("ressources/Sprites/Units/Ship_2_C_Large.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_flyingDrone.loadFromFile("ressources/Sprites/Units/FlyingDrone.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_regenerateDrone.loadFromFile("ressources/Sprites/Units/RegenerateDrone.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_armoredDrone.loadFromFile("ressources/Sprites/Units/CharRed1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_bossPlanet1.loadFromFile("ressources/Sprites/Units/bossPlanet1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_bossPlanet2.loadFromFile("ressources/Sprites/Units/bossPlanet2.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_bossPlanet3.loadFromFile("ressources/Sprites/Units/bossPlanet3.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_transportSpaceship.loadFromFile("ressources/Sprites/Units/bigSpaceship.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_fastSpaceship.loadFromFile("ressources/Sprites/Units/miniSpaceship.png")))
        std::cout << "Error on loading texture..." << std::endl;
    // TANKS
    if (!(this->_tank.loadFromFile("ressources/Sprites/Units/basicTank.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_drillTank.loadFromFile("ressources/Sprites/Units/miniTank.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_fastTank.loadFromFile("ressources/Sprites/Units/crossTank.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_crossTank.loadFromFile("ressources/Sprites/Units/cannonTank.png")))
        std::cout << "Error on loading texture..." << std::endl;
    // ARMOR SPRITE
    if (!(this->_armor.loadFromFile("ressources/Sprites/Units/spr_shield.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_freeze.loadFromFile("ressources/Sprites/Units/iceblock.png")))
        std::cout << "Error on loading texture..." << std::endl;
    //this->_pathCell.setSmooth(false);
    //this->_notWalkableCell.setSmooth(false);
    //   this->_wallCell.loadFromFile();
    // this->_mapBorder.loadFromFile();
}

SFMLEnemiesLoader::~SFMLEnemiesLoader() {

}