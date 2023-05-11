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
    int                         _globalVolume;

    std::vector<MenusButton*>   _visibleButtons;
    std::vector<sf::Sprite*>    _visibleSprites;
    std::vector<sf::Text*>      _visibleText;
    sf::Sprite                  _actualBackground;

    sf::Texture                 _planet1txt;
    sf::Texture                 _planet2txt;
    sf::Texture                 _planet3txt;

    sf::Texture                 _backgroundStars;
    sf::Texture                 _backgroundHome;
    sf::Texture                 _backgroundSingleplayer;
    sf::Texture                 _backgroundMultiplayer;
    sf::Texture                 _backgroundSettings;
    sf::Texture                 _backgroundTutorial;

    sf::Font                    _mainFont;
    sf::Font                    _fontTitle;

public:
    Menus(int winSizeX, int winSizeY, int globalVolume);
    ~Menus() = default;

    // GETTER & SETTER
    int getGlobalVolume() { return(this->_globalVolume);};

    // MENUS LOADERS
    std::string loadMenuByName(std::string name);
    void loadHome();
    void loadSingleplayer();
    void loadMultiplayer();
    void loadSettings();
    void loadTutorial();
    void loadLevelsPlanet1();
    void loadLevelsPlanet2();
    void loadLevelsPlanet3();
    void drawMenu(sf::RenderWindow &window);

    // FUNCTION
    std::string checkForClick(sf::Vector2i mousePos);
};

#endif //UNTITLED1_MENUS_HPP
