//
// Created by adrie on 02/05/2023.
//

#ifndef UNTITLED1_SFMAINSOUNDLOADER_HPP
#define UNTITLED1_SFMAINSOUNDLOADER_HPP

#include "SFML/Audio.hpp"

class SFMainSoundLoader {
private:
    sf::SoundBuffer _menuMusic;
    sf::SoundBuffer _gameMusic;
    sf::SoundBuffer _menuClick;
    sf::SoundBuffer _gamePlacementClick;
    sf::SoundBuffer _gameCoinWon;
    sf::SoundBuffer _gameCoinLoss;
    sf::SoundBuffer _gameLifeLoss;
    sf::SoundBuffer _gameSellObject;
public:
    SFMainSoundLoader();
    ~SFMainSoundLoader() = default;
    sf::SoundBuffer getMenuMusic() { return (this->_menuMusic); };
    sf::SoundBuffer getGameMusic() { return (this->_gameMusic); };
    sf::SoundBuffer getMenuClick() { return (this->_menuClick); };
    sf::SoundBuffer getGamePlacementClick() { return (this->_gamePlacementClick); };
    sf::SoundBuffer getGameCoinWon() { return (this->_gameCoinWon); };
    sf::SoundBuffer getGameCoinLoss() { return (this->_gameCoinLoss); };
    sf::SoundBuffer getGameLifeLoss() { return (this->_gameLifeLoss); };
    sf::SoundBuffer getGameSellObject() { return (this->_gameSellObject); };
};

#endif //UNTITLED1_SFMAINSOUNDLOADER_HPP