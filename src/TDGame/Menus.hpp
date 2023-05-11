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
    std::string                 _players;
    std::string                 _ipAddressField;
    bool                        _isIpEntering;

    std::vector<MenusButton*>   _visibleButtons;
    std::vector<sf::Sprite*>    _visibleSprites;
    std::vector<sf::Text*>      _visibleText;
    sf::Sprite                  _actualBackground;

    sf::Texture                 _planet1txt;
    sf::Texture                 _planet2txt;
    sf::Texture                 _planet3txt;

    sf::Texture                 _singleIcon;
    sf::Texture                 _multiIcon;
    sf::Texture                 _tutoIcon;
    sf::Texture                 _settingsIcon;


    sf::Texture                 _backgroundStars;
    sf::Texture                 _backgroundHome;
    sf::Texture                 _backgroundSingleplayer;
    sf::Texture                 _backgroundMultiplayer;
    sf::Texture                 _backgroundLevels;
    sf::Texture                 _backgroundSettings;
    sf::Texture                 _backgroundTutorial;

    sf::Font                    _mainFont;
    sf::Font                    _fontTitle;

    int                         _nbUnlockedPlanet1 = 10;
    int                         _nbUnlockedPlanet2 = 7;
    int                         _nbUnlockedPlanet3= 0;
public:
    Menus(int winSizeX, int winSizeY, int globalVolume);
    ~Menus() = default;

    // GETTER & SETTER
    int getGlobalVolume() { return(this->_globalVolume);};
    void setIpAddressField(std::string ipAddress) { this->_ipAddressField = ipAddress;  };
    std::string getIpAddressField() { return(this->_ipAddressField); };
    bool isIpEntering() { return(this->_isIpEntering); };

    // MENUS LOADERS
    std::string loadMenuByName(std::string name);
    void loadHome();
    void loadSingleplayer();
    void loadMultiplayer();
    void loadHost();
    void loadHostLobby();
    void loadJoin();
    void loadJoinTest();
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
