//
// Created by adrie on 02/05/2023.
//

#include <iostream>
#include "SFMainSoundLoader.hpp"

SFMainSoundLoader::SFMainSoundLoader() {
    bool checkError = false;
    if (!(this->_menuMusic.loadFromFile("sound.wav")))
        checkError = true;
    if (!(this->_gameMusic.loadFromFile("sound.wav")))
        checkError = true;
    if (!(this->_menuClick.loadFromFile("sound.wav")))
        checkError = true;
    if (!(this->_gamePlacementClick.loadFromFile("sound.wav")))
        checkError = true;
    if (!(this->_gameCoinWon.loadFromFile("sound.wav")))
        checkError = true;
    if (!(this->_gameCoinLoss.loadFromFile("sound.wav")))
        checkError = true;
    if (!(this->_gameLifeLoss.loadFromFile("sound.wav")))
        checkError = true;
    if (!(this->_gameSellObject.loadFromFile("sound.wav")))
        checkError = true;

    if (checkError == true) {
        std::cout << "Error on loading main sounds..." << std::endl;
        return ;
    }
}