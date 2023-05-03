//
// Created by adrie on 06/04/2023.
//

#include <iostream>

#include "SFMLTowerLoader.hpp"

SFMLTowerLoader::SFMLTowerLoader() {
    if (!(this->_support.loadFromFile("Sprites/MyTiles/TowerSupport.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_basic.loadFromFile("Sprites/MyTiles/basic_tower.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_speed.loadFromFile("Sprites/MyTiles/speed_tower.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_antiAir.loadFromFile("Sprites/MyTiles/antiAir_lvl1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_slow.loadFromFile("Sprites/MyTiles/SlowTower_lvl1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_sniper.loadFromFile("Sprites/MyTiles/SniperTower_lvl1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_splash.loadFromFile("Sprites/MyTiles/SplashTower_lvl1.png")))
        std::cout << "Error on loading texture..." << std::endl;
}

SFMLTowerLoader::~SFMLTowerLoader() {

}