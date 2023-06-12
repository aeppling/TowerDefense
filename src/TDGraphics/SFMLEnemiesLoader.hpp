//
// Created by adrie on 06/04/2023.
//

#ifndef UNTITLED1_SFMLENEMIESLOADER_HPP
#define UNTITLED1_SFMLENEMIESLOADER_HPP

#include "SFML/Graphics.hpp"
#include <memory>

class SFMLEnemiesLoader {
private:
    sf::Texture _drone;
    sf::Texture _missile;
    sf::Texture _alien;
    sf::Texture _spaceship;
    sf::Texture _flyingDrone;
    sf::Texture _regenerateDrone;
    sf::Texture _transportSpaceship;
    sf::Texture _fastSpaceship;

    sf::Texture _tank;
    sf::Texture _drillTank;
    sf::Texture _fastTank;
    sf::Texture _crossTank;

    sf::Texture _armoredDrone;

    sf::Texture _bossPlanet1;
    sf::Texture _bossPlanet2;
    sf::Texture _bossPlanet3;

    sf::Texture _freeze;
    sf::Texture _armor;
public:
    SFMLEnemiesLoader();
    ~SFMLEnemiesLoader();
    // GETTERS
    sf::Texture *getDrone() { return (&this->_drone); };
    sf::Texture *getMissile() { return (&this->_missile); };
    sf::Texture *getAlien() { return (&this->_alien); };
    sf::Texture *getSpaceship() { return (&this->_spaceship); };
    sf::Texture *getFlyingDrone() { return (&this->_flyingDrone); };
    sf::Texture *getRegenerateDrone() { return (&this->_regenerateDrone); };
    sf::Texture *getTransportSpaceship() { return (&this->_transportSpaceship); };
    sf::Texture *getFastSpaceship() { return (&this->_fastSpaceship); };

    sf::Texture *getTank() { return (&this->_tank); };
    sf::Texture *getDrillTank() { return (&this->_drillTank); };
    sf::Texture *getFastTank() { return (&this->_fastTank); };
    sf::Texture *getCrossTank() { return (&this->_crossTank); };

    sf::Texture *getArmoredDrone() { return (&this->_armoredDrone); };

    sf::Texture *getBossPlanet1() { return (&this->_bossPlanet1); };
    sf::Texture *getBossPlanet2() { return (&this->_bossPlanet2); };
    sf::Texture *getBossPlanet3() { return (&this->_bossPlanet3); };


    sf::Texture *getFreeze() { return (&this->_freeze); };
    sf::Texture *getArmor() { return (&this->_armor); };
};

#endif //UNTITLED1_SFMLENEMIESLOADER_HPP
