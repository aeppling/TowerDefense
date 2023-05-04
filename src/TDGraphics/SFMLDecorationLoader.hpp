//
// Created by adrie on 04/05/2023.
//

#ifndef UNTITLED1_SFMLDECORATIONLOADER_HPP
#define UNTITLED1_SFMLDECORATIONLOADER_HPP

#include <SFML/Graphics.hpp>

class SFMLDecorationLoader {
private:
    sf::Texture _rock1;
    sf::Texture _bush2;
    sf::Texture _tree1;
public:
    SFMLDecorationLoader();
    ~SFMLDecorationLoader();
    sf::Texture *getRock1() { return (&this->_rock1); };
    sf::Texture *getBush2() { return (&this->_bush2); };
    sf::Texture *getTree1() { return (&this->_tree1); };

};

#endif //UNTITLED1_SFMLDECORATIONLOADER_HPP
