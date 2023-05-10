//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_MENUS_HPP
#define UNTITLED1_MENUS_HPP

#include "MenusButton.hpp"

class Menus {
private:
    std::vector<MenusButton*>   _visibleButtons;
    sf::Texture                 _backgroundHome;
    sf::Texture                 _backgroundSingleplayer;
    sf::Texture                 _backgroundMultiplayer;
    sf::Texture                 _backgroundSettings;
public:
    Menus() {};
    ~Menus() = default;

    // MENUS LOADERS
    void loadHome();
    void loadSingleplayer();
    void loadMultiplayer();
    void loadSettings();
    void drawMenu(sf::RenderWindow &window);
};

#endif //UNTITLED1_MENUS_HPP
