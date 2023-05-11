//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_MENUSBUTTON_HPP
#define UNTITLED1_MENUSBUTTON_HPP

#include "SFML/Graphics.hpp"
#include "usefullStruct.hpp"

class MenusButton {
private:
    sf::RectangleShape  _rectangle;
    sf::Sprite          _icon;
    sf::Text            _text;

    int                 _posX;
    int                 _posY;
    std::string         _shortname;
public:
    MenusButton(int sizeX, int sizeY, sf::Texture *iconTexture, std::string text, std::string shortname, sf::Font &mainFont);
    ~MenusButton() = default;

    // GETTER & SETTER
    void setPosition(int posX, int posY);
    sf::RectangleShape *getRectangle() { return(&this->_rectangle); };
    sf::Sprite         *getIcon() { return(&this->_icon); };
    sf::Text           *getText() { return(&this->_text); };
    // FUNCTIONS
    std::string isClicked(int mousePosX, int mousePosY);
};

#endif //UNTITLED1_MENUSBUTTON_HPP
