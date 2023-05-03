//
// Created by adrie on 06/04/2023.
//

#ifndef UNTITLED1_SFMLTOWERLOADER_HPP
#define UNTITLED1_SFMLTOWERLOADER_HPP

#include "SFML/Graphics.hpp"
#include <memory>

class SFMLTowerLoader {
private:
    sf::Texture _support;
    sf::Texture _basic;
    sf::Texture _speed;
    sf::Texture _antiAir;
    sf::Texture _slow;
    sf::Texture _sniper;
    sf::Texture _splash;
public:
    SFMLTowerLoader();
    ~SFMLTowerLoader();
    // GETTERS
    sf::Texture *getSupport() { return (&this->_support); };
    sf::Texture *getBasic() { return (&this->_basic); };
    sf::Texture *getSpeed() { return (&this->_speed); };
    sf::Texture *getAntiAir() { return (&this->_antiAir); };
    sf::Texture *getSlow() { return (&this->_slow); };
    sf::Texture *getSniper() { return (&this->_sniper); };
    sf::Texture *getSplash() { return (&this->_splash); };
};

#endif //UNTITLED1_SFMLTOWERLOADER_HPP
