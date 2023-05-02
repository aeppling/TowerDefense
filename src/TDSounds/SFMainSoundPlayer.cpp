//
// Created by adrie on 02/05/2023.
//

#include "../TDSounds/SFMainSoundPlayer.hpp"

SFMainSoundPlayer::SFMainSoundPlayer(SFMainSoundLoader &soundLoader) {
    this->_menuMusic.setBuffer(soundLoader.getMenuMusic());
    this->_gameMusic.setBuffer(soundLoader.getGameMusic());
    this->_menuClick.setBuffer(soundLoader.getMenuClick());
    this->_gamePlacementClick.setBuffer(soundLoader.getGamePlacementClick());
    this->_gameCoinWon.setBuffer(soundLoader.getGameCoinWon());
    this->_gameCoinLoss.setBuffer(soundLoader.getGameCoinLoss());
    this->_gameLifeLoss.setBuffer(soundLoader.getGameLifeLoss());
    this->_gameSellObject.setBuffer(soundLoader.getGameSellObject());
}