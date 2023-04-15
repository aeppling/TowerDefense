//
// Created by adrie on 05/04/2023.
//

#include <iostream>
#include "SFMLSprite.hpp"
#include "SFMLLoader.hpp"
#include "../TDGame/usefullStruct.hpp"

void        SFMLSprite::setSprite(sf::Texture *texture, int cellSize, int posX, int posY, char type) {
    this->_posX = posX;
    this->_posY = posY;
    this->_type = type;
    this->_sprite.setTexture(*texture);
    float scaleFactor = static_cast<float>(cellSize) / static_cast<float>(texture->getSize().x);
    sf::IntRect textureRect(0, 0, texture->getSize().x, texture->getSize().y);
    this->_sprite.setScale(scaleFactor, scaleFactor);
    this->_sprite.setTextureRect(textureRect);
    this->_sprite.setPosition(this->_posX * cellSize + _GAME_POSITION_X, this->_posY * cellSize + _GAME_POSITION_Y);
}

void        SFMLSprite::setPosition(int cellSize) {
    this->_sprite.setPosition(this->_posX * cellSize + _GAME_POSITION_X, this->_posY * cellSize + _GAME_POSITION_Y);
}