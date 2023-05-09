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
    if (!(this->_aura.loadFromFile("Sprites/MyTiles/SpeedAura_lvl1.png")))
        std::cout << "Error on loading texture..." << std::endl;

    if (!(this->_basic2.loadFromFile("Sprites/MyTiles/basic_tower_lvl2.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_speed2.loadFromFile("Sprites/MyTiles/speed_tower_lvl2.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_antiAir2.loadFromFile("Sprites/MyTiles/antiAir_lvl2.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_slow2.loadFromFile("Sprites/MyTiles/SlowTower_lvl2.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_sniper2.loadFromFile("Sprites/MyTiles/SniperTower_lvl2.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_splash2.loadFromFile("Sprites/MyTiles/SplashTower_lvl2.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_aura2.loadFromFile("Sprites/MyTiles/SpeedAura_lvl2.png")))
        std::cout << "Error on loading texture..." << std::endl;

    if (!(this->_basic3.loadFromFile("Sprites/MyTiles/basic_tower_lvl3.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_speed3.loadFromFile("Sprites/MyTiles/speed_tower_lvl3.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_antiAir3.loadFromFile("Sprites/MyTiles/antiAir_lvl3.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_slow3.loadFromFile("Sprites/MyTiles/SlowTower_lvl3.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_sniper3.loadFromFile("Sprites/MyTiles/SniperTower_lvl3.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_splash3.loadFromFile("Sprites/MyTiles/SplashTower_lvl3.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_aura3.loadFromFile("Sprites/MyTiles/SpeedAura_lvl3.png")))
        std::cout << "Error on loading texture..." << std::endl;
}

sf::Texture *SFMLTowerLoader::getTextureFromName(std::string name, int lvl) {
    if (name == "BasicTower") {
        if (lvl == 1)
            return (&this->_basic2);
        else if (lvl == 2)
            return (&this->_basic3);
    }
    else if (name == "AttackSpeedTower"){
        if (lvl == 1)
            return (&this->_speed2);
        else if (lvl == 2)
            return (&this->_speed3);
    }
    else if (name == "AntiAirTower"){
        if (lvl == 1)
            return (&this->_antiAir2);
        else if (lvl == 2)
            return (&this->_antiAir3);
    }
    else if (name == "SlowTower"){
        if (lvl == 1)
            return (&this->_slow2);
        else if (lvl == 2)
            return (&this->_slow3);
    }
    else if (name == "SniperTower"){
        if (lvl == 1)
            return (&this->_sniper2);
        else if (lvl == 2)
            return (&this->_sniper3);
    }
    else if (name == "SplashTower"){
        if (lvl == 1)
            return (&this->_splash2);
        else if (lvl == 2)
            return (&this->_splash3);
    }
    else if (name == "SpeedAuraTower"){
        if (lvl == 1)
            return (&this->_aura2);
        else if (lvl == 2)
            return (&this->_aura3);
    }
}

SFMLTowerLoader::~SFMLTowerLoader() {

}