//
// Created by adrie on 06/04/2023.
//

#ifndef UNTITLED1_SFMLTOWERLOADER_HPP
#define UNTITLED1_SFMLTOWERLOADER_HPP

#include "SFML/Graphics.hpp"
#include <memory>

class SFMLTowerLoader {
private:
    sf::Texture _basic;
public:
    SFMLTowerLoader();
    ~SFMLTowerLoader();
    // GETTERS
    sf::Texture *getBasic() { return (&this->_basic); };
};

#endif //UNTITLED1_SFMLTOWERLOADER_HPP
