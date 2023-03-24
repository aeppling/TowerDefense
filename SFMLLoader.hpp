//
// Created by adrie on 24/03/2023.
//

#ifndef UNTITLED1_SFMLLOADER_HPP
#define UNTITLED1_SFMLLOADER_HPP

#include "SFML/Graphics.hpp"

class SFMLLoader {
private:
    sf::Texture _pathCell;
    sf::Texture _notWalkableCell;
    sf::Texture _wallCell;
    sf::Texture _mapBorder;
public:
    SFMLLoader();
    ~SFMLLoader();
};

#endif //UNTITLED1_SFMLLOADER_HPP
