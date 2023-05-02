//
// Created by adrie on 02/05/2023.
//

#ifndef UNTITLED1_SFMAINSOUNDPLAYER_HPP
#define UNTITLED1_SFMAINSOUNDPLAYER_HPP

#include "../TDSounds/SFMainSoundLoader.hpp"

class SFMainSoundPlayer {
private:
    sf::Sound _menuMusic;
    sf::Sound _gameMusic;
    sf::Sound _menuClick;
    sf::Sound _gamePlacementClick;
    sf::Sound _gameCoinWon;
    sf::Sound _gameCoinLoss;
    sf::Sound _gameLifeLoss;
    sf::Sound _gameSellObject;
public:
    SFMainSoundPlayer(SFMainSoundLoader &soundLoader);
    ~SFMainSoundPlayer() {};
    void playMenuMusic() { this->_menuMusic.play(); };
    void stopMenuMusic() { this->_menuMusic.stop(); };
    void playGameMusic() { this->_gameMusic.play(); };
    void stopGameMusic() { this->_gameMusic.stop(); };
    void playMenuClick() { this->_menuClick.play(); };
    void playGamePlacementClick() { this->_gamePlacementClick.play(); };
    void playGameCoinWon() { this->_gameCoinWon.play(); };
    void playGameCoinLoss() { this->_gameCoinLoss.play(); };
    void playLifeLoss() { this->_gameLifeLoss.play(); };
    void playGameSellObject() { this->_gameSellObject.play(); };
};
#endif //UNTITLED1_SFMAINSOUNDPLAYER_HPP
