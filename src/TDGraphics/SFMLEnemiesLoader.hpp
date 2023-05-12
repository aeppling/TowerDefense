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

    sf::Texture _armoredDrone;

    sf::Texture _freeze;
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

    sf::Texture *getArmoredDrone() { return (&this->_armoredDrone); };

    sf::Texture *getFreeze() { return (&this->_freeze); };
};

#endif //UNTITLED1_SFMLENEMIESLOADER_HPP
