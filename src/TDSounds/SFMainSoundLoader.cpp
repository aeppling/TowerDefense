//
// Created by adrie on 02/05/2023.
//

#include <iostream>
#include "SFMainSoundLoader.hpp"

SFMainSoundLoader::SFMainSoundLoader() {
    bool checkError = false;
    // SOUNDS
    if (!(this->_menuClick.loadFromFile("Sounds/menuClick.ogg")))
        checkError = true;
/*    if (!(this->_gamePlacementClick.loadFromFile("sound.wav")))
        checkError = true;*/
    if (!(this->_gameCoinWon.loadFromFile("Sounds/coinWon.ogg")))
        checkError = true;
    if (!(this->_gameCoinLoss.loadFromFile("Sounds/buySound.ogg")))
        checkError = true;
/*    if (!(this->_gameLifeLoss.loadFromFile("sound.wav")))
        checkError = true;
    if (!(this->_gameSellObject.loadFromFile("sound.wav")))
        checkError = true;*/

    if (checkError == true) {
        std::cout << "Error on loading main sounds..." << std::endl;
        return ;
    }
}