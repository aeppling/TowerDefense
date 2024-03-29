//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_MENUS_HPP
#define UNTITLED1_MENUS_HPP

#include "MenusButton.hpp"
#include "../TDPlayer/TDPlayerSave.hpp"

class Menus {
private:
    int                         _winSizeX;
    int                         _winSizeY;
  /*  int                         _globalVolume;
    int                         _musicVolume;
    int                         _soundVolume;
    int                         _difficulty;*/
    std::string                 _players;
    std::string                 _ipAddressField;
    std::string                 _ip;
    bool                        _isIpEntering;
    bool                        _isInSettings;

    sf::RectangleShape          _globalVolumeSlider;
    sf::RectangleShape          _musicVolumeSlider;
    sf::RectangleShape          _soundVolumeSlider;
    sf::RectangleShape          _globalVolumeSliderBackground;
    sf::RectangleShape          _musicVolumeSliderBackground;
    sf::RectangleShape          _soundVolumeSliderBackground;

    std::vector<MenusButton*>           _visibleButtons;
    std::vector<sf::Sprite*>            _visibleSprites;
    std::vector<sf::Text*>              _visibleText;
    std::vector<sf::RectangleShape*>    _visibleRectangle;
    sf::Sprite                          _actualBackground;

    sf::Texture                 _planet1txt;
    sf::Texture                 _planet2txt;
    sf::Texture                 _planet3txt;
    sf::Texture                 _planet2txtlocked;
    sf::Texture                 _planet3txtlocked;

    sf::Texture                 _singleIcon;
    sf::Texture                 _multiIcon;
    sf::Texture                 _tutoIcon;
    sf::Texture                 _settingsIcon;
    sf::Texture                 _hostIcon;
    sf::Texture                 _joinIcon;


    sf::Texture                 _backgroundStars;
    sf::Texture                 _backgroundHome;
    sf::Texture                 _backgroundSingleplayer;
    sf::Texture                 _backgroundLevels;
    sf::Texture                 _backgroundSettings;
    sf::Texture                 _backgroundTutorial;
    sf::Texture                 _backgroundTowerManual;
    sf::Texture                 _backgroundUnitManual;
    sf::Texture                 _backgroundGameWon;
    sf::Texture                 _backgroundGameLost;

    sf::Font                    _mainFont;
    sf::Font                    _fontTitle;

    TDPlayerSave                &_playerData;
public:
    Menus(int winSizeX, int winSizeY, TDPlayerSave &playerData);
    ~Menus() = default;

    // GETTER & SETTER
    int getGlobalVolume() { return(this->_playerData.getGlobalVolume());};
    void setIpAddressField(std::string ipAddress) { this->_ipAddressField = ipAddress;  };
    std::string getIpAddressField() { return(this->_ipAddressField); };
    bool isIpEntering() { return(this->_isIpEntering); };
    void setDifficultyEasy();
    void setDifficultyNormal();
    void setDifficultyHard();
    int getDifficulty() { return(this->_playerData.getDifficulty()); };
    // CREATOR
    void createText(std::string text, sf::Font &font, int characterSize, int posX, int posY);
    void createSlider(float value, float posX, float posY, std::string type);
    // MENUS LOADERS
    std::string loadMenuByName(std::string name);
    void loadHome();
    void loadSingleplayer();
    void loadMultiplayer();
    void loadHost(std::string hostIpAddress);
    void loadHostLobby();
    void loadJoin();
    void loadJoinTest();
    void loadSettings();
    void loadResetSettingsConfirm();
    void reloadVolume(int newVolume, std::string type);
    void loadTutorial();
    void loadTowerManualScreen();
    void loadUnitManualScreen();
    void loadLevelsPlanet1();
    void loadLevelsPlanet2();
    void loadLevelsPlanet3();
    void loadWonScreen();
    void loadLooseScreen();
    void drawMenu(sf::RenderWindow &window);
    void setIp(std::string ip) { this->_ip = ip; };

    // DELETOR
    void deleteVisibleButtons() {
        if (this->_visibleButtons.empty())
            return;
        for (MenusButton *element: this->_visibleButtons) {
            delete element;
        }
        this->_visibleButtons.clear();
    }
    void deleteVisibleRectangle() {
        if (this->_visibleRectangle.empty())
            return;
        for (sf::RectangleShape *element: this->_visibleRectangle) {
            delete element;
        }
        this->_visibleRectangle.clear();
    }
    void deleteVisibleText() {
        if (this->_visibleText.empty())
            return;
        for (sf::Text *element: this->_visibleText) {
            delete element;
        }
        this->_visibleText.clear();
    }
    void deleteVisibleSprites() {
        if (this->_visibleSprites.empty())
            return;
        for (sf::Sprite *element: this->_visibleSprites) {
            delete element;
        }
        this->_visibleSprites.clear();
    }
    // FUNCTION
    std::string checkForClick(sf::Vector2i mousePos);
    bool checkIfVolumeClicked(sf::Vector2i mousePos, TDPlayerSave &playerSave, std::string saveFile);
};

#endif //UNTITLED1_MENUS_HPP
