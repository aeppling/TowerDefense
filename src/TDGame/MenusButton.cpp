//
// Created by adrie on 10/05/2023.
//

#include "MenusButton.hpp"

MenusButton::MenusButton(int sizeX, int sizeY, sf::Texture *iconTexture, std::string text, std::string shortname) : _shortname(shortname) {
    // SET TEXT
    this->_text.setString(text);
    // SET ICON TEXTURE
    if (iconTexture != nullptr) {
        this->_icon.setTexture(*iconTexture);
        this->_hasIcon = true;
    } else
        this->_hasIcon = false;
    // SET BUTTON RECTANGLE
    this->_rectangle.setSize(sf::Vector2f(sizeX, sizeY));
    this->_rectangle.setFillColor(sf::Color::Transparent);
    this->_rectangle.setOutlineThickness(3);
    this->_rectangle.setOutlineColor(sf::Color::White);
    sf::Vector2f newOrigin(this->_rectangle.getLocalBounds().width / 2.f, this->_rectangle.getLocalBounds().height / 2.f);
    this->_rectangle.setOrigin(newOrigin);
}

void MenusButton::setPosition(int posX, int posY) {
    this->_posX = posX;
    this->_posY = posY;
    this->_rectangle.setPosition(posX, posY);
}

std::string MenusButton::isClicked(int mousePosX, int mousePosY) {
    if (this->_rectangle.getGlobalBounds().contains(mousePosX + _GAME_POSITION_X, mousePosY + _GAME_POSITION_Y))
        return (this->_shortname);
    else
        return ("no");
}