//
// Created by adrie on 10/05/2023.
//

#include <iostream>

#include "Menus.hpp"

Menus::Menus(int winSizeX, int winSizeY) : _winSizeX(winSizeX), _winSizeY(winSizeY) {

    if (this->_planet1txt.loadFromFile("Sprites/Planets/planet03.png"))
        std::cout << "Planet sprite not loaded correctly" << std::endl;
    if (this->_planet2txt.loadFromFile("Sprites/Planets/planet07.png"))
        std::cout << "Planet sprite not loaded correctly" << std::endl;
    if (this->_planet3txt.loadFromFile("Sprites/Planets/planet09.png"))
        std::cout << "Planet sprite not loaded correctly" << std::endl;
    //
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
  /*  this->_nbPlanet1Unlocked = 10;
    this->_nbPlanet2Unlocked = 7;
    this->_nbPlanet3Unlocked = 0;*/
}

void Menus::loadHome() {
    this->_visibleButtons.clear();
    this->_visibleSprites.clear();

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
    this->_visibleSprites.clear();

    // BUTTONS SETUP
    MenusButton *world1 = new MenusButton(400, 600, nullptr, "Planet-1", "planet1", false, this->_mainFont);
    MenusButton *world2 = new MenusButton(400, 600, nullptr, "Planet-2", "planet2", false, this->_mainFont);
    MenusButton *world3 = new MenusButton(400, 600, nullptr, "Planet-3", "planet3", false, this->_mainFont);
    MenusButton *backhome = new MenusButton(400, 80, nullptr, "Back To Home", "home", false, this->_mainFont);
    world1->getText()->setCharacterSize(40);
    world2->getText()->setCharacterSize(40);
    world3->getText()->setCharacterSize(40);

    int offset = (_winSizeX / 5) + 70;
    world1->setPosition(offset, 500);
    world2->setPosition(offset + 500, 500);
    world3->setPosition(offset + 1000, 500);
    world1->getText()->setPosition(world1->getText()->getPosition().x - 50, world1->getText()->getPosition().y + 170);
    world2->getText()->setPosition(world2->getText()->getPosition().x - 50, world2->getText()->getPosition().y + 170);
    world3->getText()->setPosition(world3->getText()->getPosition().x - 50, world3->getText()->getPosition().y + 170);
    backhome->setPosition(_winSizeX / 2, 900);

    this->_visibleButtons.push_back(world1);
    this->_visibleButtons.push_back(world2);
    this->_visibleButtons.push_back(world3);
    this->_visibleButtons.push_back(backhome);

    // BACKGROUND SETUP
    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);

    // OTHERS SPRITE SET UP

    sf::Sprite *planet1Spr = new sf::Sprite;
    sf::Sprite *planet2Spr = new sf::Sprite;
    sf::Sprite *planet3Spr = new sf::Sprite;

    planet1Spr->setTexture(this->_planet1txt);
    planet2Spr->setTexture(this->_planet2txt);
    planet3Spr->setTexture(this->_planet3txt);

    sf::Vector2f newOriginText1(planet1Spr->getLocalBounds().width / 2.f, planet1Spr->getLocalBounds().height / 2.f);
    planet1Spr->setOrigin(newOriginText1);
    sf::Vector2f newOriginText2(planet2Spr->getLocalBounds().width / 2.f, planet2Spr->getLocalBounds().height / 2.f);
    planet2Spr->setOrigin(newOriginText2);
    sf::Vector2f newOriginText3(planet3Spr->getLocalBounds().width / 2.f, planet3Spr->getLocalBounds().height / 2.f);
    planet3Spr->setOrigin(newOriginText3);

    planet1Spr->setPosition(offset, 400);
    planet2Spr->setPosition(offset + 500, 400);
    planet3Spr->setPosition(offset + 1000, 400);
    planet1Spr->setScale(0.25, 0.25);
    planet2Spr->setScale(0.25, 0.25);
    planet3Spr->setScale(0.25, 0.25);

    this->_visibleSprites.push_back(planet1Spr);
    this->_visibleSprites.push_back(planet2Spr);
    this->_visibleSprites.push_back(planet3Spr);
}

void Menus::loadMultiplayer() {
    this->_visibleButtons.clear();
    this->_visibleSprites.clear();

    MenusButton *backhome = new MenusButton(400, 80, nullptr, "Back To Home", "home", false, this->_mainFont);

    backhome->setPosition(_winSizeX / 2, 900);

    this->_visibleButtons.push_back(backhome);

    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
}

void Menus::loadSettings() {
    this->_visibleButtons.clear();
    this->_visibleSprites.clear();

    MenusButton *backhome = new MenusButton(400, 80, nullptr, "Back To Home", "home", false, this->_mainFont);

    backhome->setPosition(_winSizeX / 2, 900);

    this->_visibleButtons.push_back(backhome);

    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
}

void Menus::loadTutorial() {
    this->_visibleButtons.clear();
    this->_visibleSprites.clear();

    MenusButton *backhome = new MenusButton(400, 80, nullptr, "Back To Home", "home", false, this->_mainFont);

    backhome->setPosition(_winSizeX / 2, 900);

    this->_visibleButtons.push_back(backhome);

    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
}

void Menus::loadLevelsPlanet1() {
    this->_visibleButtons.clear();
    this->_visibleSprites.clear();

    // BACK BUTTON & BACKGROUND
    MenusButton *back = new MenusButton(400, 80, nullptr, "Back To Planets", "singleplayer", false,
                                        this->_mainFont);
    back->setPosition(_winSizeX / 2, 900);
    this->_visibleButtons.push_back(back);
    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
    // LEVELS SET
    int number_of_level = 10;
    int i = 0;
    int vertical_offset = 0;
    int horizontal_offset = 0;
    while (i < number_of_level) {
        if (i == 5) {
            vertical_offset = 300;
            horizontal_offset = 0;
        }
        std::string textDisplayStr("Level " + std::to_string(i + 1));
        std::string shortNameStr("planet1level" + std::to_string(i + 1));
        MenusButton *newLevel = new MenusButton(200, 200, nullptr, textDisplayStr, shortNameStr, false, this->_mainFont);
        newLevel->setPosition(360 + (horizontal_offset * 300), 350 + vertical_offset);
        horizontal_offset++;
        this->_visibleButtons.push_back(newLevel);
        i++;
    }
}

void Menus::loadLevelsPlanet2() {
    this->_visibleButtons.clear();
    this->_visibleSprites.clear();

    // BACK BUTTON & BACKGROUND
    MenusButton *back = new MenusButton(400, 80, nullptr, "Back To Planets", "singleplayer", false,
                                        this->_mainFont);
    back->setPosition(_winSizeX / 2, 900);
    this->_visibleButtons.push_back(back);
    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
    // LEVELS SET
    int number_of_level = 10;
    int i = 0;
    int vertical_offset = 0;
    int horizontal_offset = 0;
    while (i < number_of_level) {
        if (i == 5) {
            vertical_offset = 300;
            horizontal_offset = 0;
        }
        std::string textDisplayStr("Level " + std::to_string(i + 1));
        std::string shortNameStr("planet2level" + std::to_string(i + 1));
        MenusButton *newLevel = new MenusButton(200, 200, nullptr, textDisplayStr, shortNameStr, false, this->_mainFont);
        newLevel->setPosition(360 + (horizontal_offset * 300), 350 + vertical_offset);
        horizontal_offset++;
        this->_visibleButtons.push_back(newLevel);
        i++;
    }
}

void Menus::loadLevelsPlanet3() {
    this->_visibleButtons.clear();
    this->_visibleSprites.clear();

    // BACK BUTTON & BACKGROUND
    MenusButton *back = new MenusButton(400, 80, nullptr, "Back To Planets", "singleplayer", false,
                                        this->_mainFont);
    back->setPosition(_winSizeX / 2, 900);
    this->_visibleButtons.push_back(back);
    this->_actualBackground.setTexture(this->_backgroundHome);
    this->_actualBackground.setPosition(this->_winSizeX / 4.2, 0);
    this->_actualBackground.setScale(0.5, 0.5);
    // LEVELS SET
    int number_of_level = 10;
    int i = 0;
    int vertical_offset = 0;
    int horizontal_offset = 0;
    while (i < number_of_level) {
        if (i == 5) {
            vertical_offset = 300;
            horizontal_offset = 0;
        }
        std::string textDisplayStr("Level " + std::to_string(i + 1));
        std::string shortNameStr("planet3level" + std::to_string(i + 1));
        MenusButton *newLevel = new MenusButton(200, 200, nullptr, textDisplayStr, shortNameStr, false, this->_mainFont);
        newLevel->setPosition(360 + (horizontal_offset * 300), 350 + vertical_offset);
        horizontal_offset++;
        this->_visibleButtons.push_back(newLevel);
        i++;
    }
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
    i = 0;
    while (i < this->_visibleSprites.size()) {
        window.draw(*this->_visibleSprites.at(i));
        i++;
    }
}

std::string Menus::loadMenuByName(std::string name) {
    if (name == "singleplayer") {
        this->loadSingleplayer();
        return ("no");
    }
    else if (name == "multiplayer") {
        this->loadMultiplayer();
        return ("no");
    }
    else if (name == "settings") {
        this->loadSettings();
        return ("no");
    }
    else if (name == "home") {
        this->loadHome();
        return ("no");
    }
    else if (name == "planet1") {
        this->loadLevelsPlanet1();
        return ("no");
    }
    else if (name == "planet2") {
        this->loadLevelsPlanet2();
        return ("no");
    }
    else if (name == "planet3") {
        this->loadLevelsPlanet3();
        return ("no");
    }
    else
        return (name); // COMPACT WITH DIFFICULTY ????
    // ELSE RETURN BECAUSE IT IS A LEVEL & PLANET INFORMATION
}

std::string Menus::checkForClick(sf::Vector2i mousePos) {
    int i = 0;

    std::string whichClick;
    while (i < this->_visibleButtons.size()) {
        whichClick = this->_visibleButtons.at(i)->isClicked(mousePos.x, mousePos.y);
        if (whichClick == "exit")
            return (whichClick);
        else if (whichClick != "no") {
            std::string answer = this->loadMenuByName(whichClick);
            if (answer != "no")
                return (answer);
            else
                break;
        }
        i++;
    }
    return ("no");
}