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
public:
    SFMLMissileLoader();
    ~SFMLMissileLoader();
    // GETTERS
    sf::Texture *getBasic() { return (&this->_basic); };
    sf::Texture *getSpeed() { return (&this->_speed); };
};

#endif //UNTITLED1_SFMLMISSILELOADER_HPP
