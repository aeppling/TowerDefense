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
    std::shared_ptr<sf::Sprite>      _sprite;
public:
    SFMLSprite();
    ~SFMLSprite();
    int                              getPosX() { return (this->_posX);};
    int                              getPosY() { return (this->_posY);};
    std::shared_ptr<sf::Sprite>      getSprite() { return (this->_sprite);};
    void                             setSprite(sf::Texture texture) { this->_sprite->setTexture(texture); };
};

#endif //UNTITLED1_SFMLSPRITE_HPP
