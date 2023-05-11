//
// Created by adrie on 10/05/2023.
//

#include "MenusButton.hpp"

MenusButton::MenusButton(int sizeX, int sizeY, sf::Texture *iconTexture, std::string text, std::string shortname, sf::Font &mainFont) : _shortname(shortname) {
    // SET TEXT
    this->_text.setString(text);
    this->_text.setFont(mainFont);
    this->_text.setCharacterSize(24);
    sf::Vector2f newOriginText(this->_text.getLocalBounds().width / 2.f, this->_text.getLocalBounds().height / 2.f);
    this->_text.setOrigin(newOriginText);
    // SET BUTTON RECTANGLE
    this->_rectangle.setSize(sf::Vector2f(sizeX, sizeY));
    this->_rectangle.setFillColor(sf::Color::Transparent);
    this->_rectangle.setOutlineThickness(3);
    this->_rectangle.setOutlineColor(sf::Color::White);
    // ERASE BORDERS
    sf::Vector2f newOrigin(this->_rectangle.getLocalBounds().width / 2.f, this->_rectangle.getLocalBounds().height / 2.f);
    this->_rectangle.setOrigin(newOrigin);
}

void MenusButton::setPosition(int posX, int posY) {
    this->_posX = posX;
    this->_posY = posY;
    this->_rectangle.setPosition((float)posX, (float)posY);
    this->_text.setPosition((float)posX, (float)posY - 10);
}

std::string MenusButton::isClicked(int mousePosX, int mousePosY) {
    if (this->_rectangle.getGlobalBounds().contains(mousePosX, mousePosY))
        return (this->_shortname);
    else
        return ("no");
}