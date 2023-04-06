//
// Created by adrie on 06/04/2023.
//

#ifndef UNTITLED1_SFMLMAPRELOADER_HPP
#define UNTITLED1_SFMLMAPRELOADER_HPP

#include "SFML/Graphics.hpp"
#include <memory>

class SFMLMapReloader {
private:
    sf::Texture _pathCell;
    sf::Texture _wallCell;
public:
    SFMLMapReloader();
    ~SFMLMapReloader() {};
    // GETTERS
    sf::Texture *getPathCell() { return (&this->_pathCell); }
    sf::Texture *getWallCell() { return (&this->_wallCell); }
};

#endif //UNTITLED1_SFMLMAPRELOADER_HPP
