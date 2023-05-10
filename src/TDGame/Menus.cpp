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
    this->_visibleButtons.clear();

    MenusButton *world1 = new MenusButton(400, 600, nullptr, "Planet-1", "planet1", false, this->_mainFont);
    MenusButton *world2 = new MenusButton(400, 600, nullptr, "Planet-2", "planet2", false, this->_mainFont);
    MenusButton *backhome = new MenusButton(400, 80, nullptr, "Back To Home", "home", false, this->_mainFont);

    world1->setPosition(_winSizeX / 3, 500);
    world2->setPosition(_winSizeX / 1.7, 500);
    backhome->setPosition(_winSizeX / 2, 900);

    this->_visibleButtons.push_back(world1);
    this->_visibleButtons.push_back(world2);
    this->_visibleButtons.push_back(backhome);

    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
}

void Menus::loadMultiplayer() {
    this->_visibleButtons.clear();

    MenusButton *backhome = new MenusButton(400, 80, nullptr, "Back To Home", "home", false, this->_mainFont);

    backhome->setPosition(_winSizeX / 2, 900);

    this->_visibleButtons.push_back(backhome);

    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
}

void Menus::loadSettings() {
    this->_visibleButtons.clear();

    MenusButton *backhome = new MenusButton(400, 80, nullptr, "Back To Home", "home", false, this->_mainFont);

    backhome->setPosition(_winSizeX / 2, 900);

    this->_visibleButtons.push_back(backhome);

    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
}

void Menus::loadTutorial() {
    this->_visibleButtons.clear();

    MenusButton *backhome = new MenusButton(400, 80, nullptr, "Back To Home", "home", false, this->_mainFont);

    backhome->setPosition(_winSizeX / 2, 900);

    this->_visibleButtons.push_back(backhome);

    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
}

void Menus::loadLevelsPlanet1() {
    this->_visibleButtons.clear();

    MenusButton *back = new MenusButton(400, 80, nullptr, "Back To Planets", "singleplayer", false, this->_mainFont);

    back->setPosition(_winSizeX / 2, 900);

    this->_visibleButtons.push_back(back);

    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
}

void Menus::loadLevelsPlanet2() {
    this->_visibleButtons.clear();

    MenusButton *backhome = new MenusButton(400, 80, nullptr, "Back To Home", "home", false, this->_mainFont);

    backhome->setPosition(_winSizeX / 2, 900);

    this->_visibleButtons.push_back(backhome);

    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
}

void Menus::loadLevelsPlanet3() {
    this->_visibleButtons.clear();

    MenusButton *backhome = new MenusButton(400, 80, nullptr, "Back To Home", "home", false, this->_mainFont);

    backhome->setPosition(_winSizeX / 2, 900);

    this->_visibleButtons.push_back(backhome);

    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
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

void Menus::loadMenuByName(std::string name) {
    if (name == "singleplayer")
        this->loadSingleplayer();
    else if (name == "multiplayer")
        this->loadMultiplayer();
    else if (name == "settings")
        this->loadSettings();
    else if (name == "home")
        this->loadHome();
    else if (name == "planet1")
        this->loadLevelsPlanet1();
    else if (name == "planet2")
        this->loadLevelsPlanet2();
    else if (name == "planet3")
        this->loadLevelsPlanet3();
}

std::string Menus::checkForClick(sf::Vector2i mousePos) {
    int i = 0;

    std::string whichClick;
    while (i < this->_visibleButtons.size()) {
        whichClick = this->_visibleButtons.at(i)->isClicked(mousePos.x, mousePos.y);
        if (whichClick == "exit")
            return (whichClick);
        else if (whichClick != "no") {
            this->loadMenuByName(whichClick);
            break;
        }
        i++;
    }
}