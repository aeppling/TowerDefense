//
// Created by adrie on 05/04/2023.
//

#ifndef UNTITLED1_SFMLSPRITE_HPP
#define UNTITLED1_SFMLSPRITE_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

class SFMLSprite {
private:
    int                              _posX;
    int                              _posY;
    sf::Sprite                       _sprite;
    char                             _type;
public:
    SFMLSprite() {};
    ~SFMLSprite() {};
    int                              getPosX() { return (this->_posX);};
    int                              getPosY() { return (this->_posY);};
    sf::Sprite                       getSprite() { return (this->_sprite);};
    void                             setSprite(sf::Texture *texture, int cellSize, int posX, int posY, char type);
    void                             setPosition(int cellSize);
    char                             getType() { return (this->_type); };
    void                             setType(char type) { this->_type = type; };

};

#endif //UNTITLED1_SFMLSPRITE_HPP
