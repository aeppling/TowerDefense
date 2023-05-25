//
// Created by adrie on 06/04/2023.
//

#include <iostream>

#include "SFMLTowerLoader.hpp"

SFMLTowerLoader::SFMLTowerLoader() {
    if (!(this->_support.loadFromFile("ressources/Sprites/Towers/TowerSupport.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_basic.loadFromFile("ressources/Sprites/Towers/basic_tower.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_speed.loadFromFile("ressources/Sprites/Towers/speed_tower.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_antiAir.loadFromFile("ressources/Sprites/Towers/antiAir_lvl1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_slow.loadFromFile("ressources/Sprites/Towers/SlowTower_lvl1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_sniper.loadFromFile("ressources/Sprites/Towers/SniperTower_lvl1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_splash.loadFromFile("ressources/Sprites/Towers/SplashTower_lvl1.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_aura.loadFromFile("ressources/Sprites/Towers/SpeedAura_lvl1.png")))
        std::cout << "Error on loading texture..." << std::endl;

    if (!(this->_basic2.loadFromFile("ressources/Sprites/Towers/basic_tower_lvl2.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_speed2.loadFromFile("ressources/Sprites/Towers/speed_tower_lvl2.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_antiAir2.loadFromFile("ressources/Sprites/Towers/antiAir_lvl2.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_slow2.loadFromFile("ressources/Sprites/Towers/SlowTower_lvl2.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_sniper2.loadFromFile("ressources/Sprites/Towers/SniperTower_lvl2.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_splash2.loadFromFile("ressources/Sprites/Towers/SplashTower_lvl2.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_aura2.loadFromFile("ressources/Sprites/Towers/SpeedAura_lvl2.png")))
        std::cout << "Error on loading texture..." << std::endl;

    if (!(this->_basic3.loadFromFile("ressources/Sprites/Towers/basic_tower_lvl3.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_speed3.loadFromFile("ressources/Sprites/Towers/speed_tower_lvl3.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_antiAir3.loadFromFile("ressources/Sprites/Towers/antiAir_lvl3.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_slow3.loadFromFile("ressources/Sprites/Towers/SlowTower_lvl3.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_sniper3.loadFromFile("ressources/Sprites/Towers/SniperTower_lvl3.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_splash3.loadFromFile("ressources/Sprites/Towers/SplashTower_lvl3.png")))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_aura3.loadFromFile("ressources/Sprites/Towers/SpeedAura_lvl3.png")))
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