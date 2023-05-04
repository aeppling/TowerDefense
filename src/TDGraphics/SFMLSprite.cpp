//
// Created by adrie on 05/04/2023.
//

#include <iostream>
#include "SFMLSprite.hpp"
#include "SFMLLoader.hpp"
#include "../TDGame/usefullStruct.hpp"

void        SFMLSprite::setSprite(sf::Texture *texture, int cellSize, int posX, int posY, char type, float scale) {
    this->_posX = posX;
    this->_posY = posY;
    this->_type = type;
    this->_sprite.setTexture(*texture);
    float scaleFactor = static_cast<float>(cellSize) / static_cast<float>(texture->getSize().x);
    sf::IntRect textureRect(0, 0, texture->getSize().x, texture->getSize().y);
    if ((this->_sprite.getTexture()->getSize().x == 128) && (this->_sprite.getTexture()->getSize().y == 200)){
        sf::Vector2f newOrigin(this->_sprite.getLocalBounds().width / 5.5f, this->_sprite.getLocalBounds().height / 2.5f);
        this->_sprite.setOrigin(newOrigin);
    }
    this->_sprite.setScale(scaleFactor * scale, scaleFactor * scale);
    this->_sprite.setTextureRect(textureRect);
    this->_sprite.setPosition(this->_posX * cellSize + _GAME_POSITION_X, this->_posY * cellSize + _GAME_POSITION_Y);
}

void        SFMLSprite::setSpriteCutted(sf::Texture *texture, int cellSize, int posX, int posY, char type, float scale) {
    this->_posX = posX;
    this->_posY = posY;
    this->_type = type;
    this->_sprite.setTexture(*texture);
    float scaleFactor = static_cast<float>(cellSize) / static_cast<float>(texture->getSize().x);
    sf::IntRect textureRect(0, 72, texture->getSize().x, texture->getSize().y - 72);
    this->_sprite.setScale(scaleFactor * scale, scaleFactor * scale);
    this->_sprite.setTextureRect(textureRect);
    this->_sprite.setPosition(this->_posX * cellSize + _GAME_POSITION_X, this->_posY * cellSize + _GAME_POSITION_Y);
    if (type == 'B') {
        sf::Color newcolor(77, 250, 255, 155);
        this->_sprite.setColor(newcolor);
    }
}

void        SFMLSprite::setPosition(int cellSize) {
    this->_sprite.setPosition(this->_posX * cellSize + _GAME_POSITION_X, this->_posY * cellSize + _GAME_POSITION_Y);
}