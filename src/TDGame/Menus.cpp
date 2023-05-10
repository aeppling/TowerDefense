//
// Created by adrie on 10/05/2023.
//

#include <iostream>

#include "Menus.hpp"

Menus::Menus(int winSizeX, int winSizeY) : _winSizeX(winSizeX), _winSizeY(winSizeY) {
    if (!this->_backgroundStars.loadFromFile("Sprites/stars_texture.png"))
        std::cout << "Error on loading texture..." << std::endl;
    if (!(this->_backgroundHome.loadFromFile("Sprites/Backgrounds/BattleTankBackground.png")))
        std::cout << "Error on loading menus textures..." << std::endl;
    if (!(this->_backgroundSingleplayer.loadFromFile("Sprites/Units/CharRed1.png")))
        std::cout << "Error on loading menus textures..." << std::endl;
    if (!(this->_backgroundMultiplayer.loadFromFile("Sprites/Units/CharRed1.png")))
        std::cout << "Error on loading menus textures..." << std::endl;
    if (!(this->_backgroundSettings.loadFromFile("Sprites/Units/CharRed1.png")))
        std::cout << "Error on loading menus textures..." << std::endl;
    if (!(this->_backgroundTutorial.loadFromFile("Sprites/Units/CharRed1.png")))
        std::cout << "Error on loading menus textures..." << std::endl;
    if (!(this->_mainFont.loadFromFile("Fonts/neuropol.otf")))
        std::cout << "Error on loading menus textures..." << std::endl;
}

void Menus::loadHome() {
    this->_visibleButtons.clear();

    MenusButton *singleplayerButton = new MenusButton(300, 70, nullptr, "Singleplayer", "singleplayer", false, this->_mainFont);
    MenusButton *multiplayerButton = new MenusButton(300, 70, nullptr, "Multiplayer", "multiplayer", false, this->_mainFont);
    MenusButton *settingsButton = new MenusButton(300, 70, nullptr, "Settings", "settings", false, this->_mainFont);
    MenusButton *exitButton = new MenusButton(300, 70, nullptr, "Exit Game", "exit", false, this->_mainFont);

    singleplayerButton->setPosition(_winSizeX / 2, 400);
    multiplayerButton->setPosition(_winSizeX / 2, 500);
    settingsButton->setPosition(_winSizeX / 2, 600);
    exitButton->setPosition(_winSizeX / 2, 800);

    this->_visibleButtons.push_back(singleplayerButton);
    this->_visibleButtons.push_back(multiplayerButton);
    this->_visibleButtons.push_back(settingsButton);
    this->_visibleButtons.push_back(exitButton);

    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
}

void Menus::loadSingleplayer() {

}

void Menus::loadMultiplayer() {

}

void Menus::loadSettings() {

}

void Menus::drawMenu(sf::RenderWindow &window) {
    sf::Sprite backgroundStarsSpr(this->_backgroundStars);
    window.draw(backgroundStarsSpr);
//    window.draw(this->_actualBackground);
    int i = 0;
    while (i < this->_visibleButtons.size()) {
       if (this->_visibleButtons.at(i)->hasIcon())
            window.draw(*this->_visibleButtons.at(i)->getIcon());
        window.draw(*this->_visibleButtons.at(i)->getText());
        window.draw(*this->_visibleButtons.at(i)->getRectangle());
        i++;
    }
}