//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_MENUS_HPP
#define UNTITLED1_MENUS_HPP

#include "MenusButton.hpp"

class Menus {
private:
    int                         _winSizeX;
    int                         _winSizeY;

    std::vector<MenusButton*>   _visibleButtons;
    sf::Sprite                  _actualBackground;

    sf::Texture                 _backgroundStars;
    sf::Texture                 _backgroundHome;
    sf::Texture                 _backgroundSingleplayer;
    sf::Texture                 _backgroundMultiplayer;
    sf::Texture                 _backgroundSettings;
    sf::Texture                 _backgroundTutorial;

    sf::Font                    _mainFont;
public:
    Menus(int winSizeX, int winSizeY);
    ~Menus() = default;

    // MENUS LOADERS
    void loadMenuByName(std::string name);
    void loadHome();
    void loadSingleplayer();
    void loadMultiplayer();
    void loadSettings();
    void loadTutorial();
    void drawMenu(sf::RenderWindow &window);

    // FUNCTION
    void checkForClick(sf::Vector2i mousePos);
};

#endif //UNTITLED1_MENUS_HPP
