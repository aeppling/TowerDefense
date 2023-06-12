//
// Created by adrie on 02/05/2023.
//

#include <iostream>
#include "SFMainSoundLoader.hpp"

SFMainSoundLoader::SFMainSoundLoader() {
    bool checkError = false;
    // SOUNDS
    if (!(this->_menuClick.loadFromFile("ressources/Sounds/menuClick.ogg")))
        checkError = true;
/*    if (!(this->_gamePlacementClick.loadFromFile("sound.wav")))
        checkError = true;*/
    if (!(this->_gamePlacementClick.loadFromFile("ressources/Sounds/coinLoss.ogg")))
        checkError = true;
    if (!(this->_gameCoinLoss.loadFromFile("ressources/Sounds/buySound.ogg")))
        checkError = true;
    if (!(this->_gameCoinWon.loadFromFile("ressources/Sounds/coinWon.ogg")))
        checkError = true;
    if (!(this->_waveClear.loadFromFile("ressources/Sounds/waveClear.ogg")))
        checkError = true;
   if (!(this->_gameLifeLoss.loadFromFile("ressources/Sounds/LowBassHit.wav")))
        checkError = true;
/*    if (!(this->_gameSellObject.loadFromFile("sound.wav")))
        checkError = true;*/

    if (checkError == true) {
        std::cout << "Error on loading main sounds..." << std::endl;
        return ;
    }
}