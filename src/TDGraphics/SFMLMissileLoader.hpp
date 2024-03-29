//
// Created by adrie on 12/04/2023.
//

#ifndef UNTITLED1_SFMLMISSILELOADER_HPP
#define UNTITLED1_SFMLMISSILELOADER_HPP

#include "SFML/Graphics.hpp"
#include <memory>

class SFMLMissileLoader {
private:
    sf::Texture _basic;
    sf::Texture _speed;
    sf::Texture _antiAir;
    sf::Texture _slow;
    sf::Texture _sniper;
    sf::Texture _splash;
    sf::Texture _explosion1;
public:
    SFMLMissileLoader();
    ~SFMLMissileLoader();
    // GETTERS
    sf::Texture *getBasic() { return (&this->_basic); };
    sf::Texture *getSpeed() { return (&this->_speed); };
    sf::Texture *getAntiAir() { return (&this->_antiAir); };
    sf::Texture *getSlow() { return (&this->_slow); };
    sf::Texture *getSniper() { return (&this->_sniper); };
    sf::Texture *getSplash() { return (&this->_splash); };
    sf::Texture *getExplosion1() { return (&this->_explosion1); };
};

#endif //UNTITLED1_SFMLMISSILELOADER_HPP
