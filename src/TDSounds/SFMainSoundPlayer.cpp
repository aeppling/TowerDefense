//
// Created by adrie on 02/05/2023.
//

#include "../TDSounds/SFMainSoundPlayer.hpp"
#include <iostream>

SFMainSoundPlayer::SFMainSoundPlayer(SFMainSoundLoader &soundLoader, unsigned int globalVolume, unsigned int musicVolume, unsigned int soundVolume) {
    bool checkError = false;
    this->_musicVolume = musicVolume;
    this->_soundVolume = soundVolume;
    this->_globalVolume = globalVolume;
    // MUSIC
    if (!(this->_menuMusic.openFromFile("Music/menu_music.ogg")))
        checkError = true;
    if (!(this->_gameMusic1.openFromFile("Music/game_music1.ogg")))
        checkError = true;
    if (!(this->_gameMusic2.openFromFile("Music/game_music2.ogg")))
        checkError = true;
    if (!(this->_gameMusicChill.openFromFile("Music/game_music_chill.ogg")))
        checkError = true;
    if (!(this->_gameMusicEndWave.openFromFile("Music/game_music_endwave.ogg")))
        checkError = true;
    if (!(this->_gameMusicFaster.openFromFile("Music/game_music_faster.ogg")))
        checkError = true;
    if (checkError == true) {
        std::cout << "Error on loading main sounds..." << std::endl;
        return ;
    }

    sf::Listener::setGlobalVolume((float)this->_globalVolume);

    this->_menuMusic.setVolume((float)this->_musicVolume);
    this->_gameMusic1.setVolume((float)this->_musicVolume);
    this->_gameMusic2.setVolume((float)this->_musicVolume);
    this->_gameMusicChill.setVolume((float)this->_musicVolume);
    this->_gameMusicEndWave.setVolume((float)this->_musicVolume);
    this->_gameMusicFaster.setVolume((float)this->_musicVolume);

    // SOUNDS
    this->_menuClick.setBuffer(*soundLoader.getMenuClick());
    this->_gamePlacementClick.setBuffer(*soundLoader.getGamePlacementClick());
    this->_gameCoinLoss.setBuffer(*soundLoader.getGameCoinLoss());
    this->_gameCoinWon.setBuffer(*soundLoader.getGameCoinWon());
    this->_waveClear.setBuffer(*soundLoader.getWaveClear());
    this->_gameLifeLoss.setBuffer(*soundLoader.getGameLifeLoss());
    // this->_gameSellObject.setBuffer(soundLoader.getGameSellObject());

    this->_menuClick.setVolume((float)this->_soundVolume / 4);
    this->_gamePlacementClick.setVolume((float)this->_soundVolume);
    this->_gameCoinWon.setVolume((float)this->_soundVolume);
    this->_waveClear.setVolume((float)this->_soundVolume / 8);
    this->_gameCoinLoss.setVolume((float)this->_soundVolume);
    this->_gameLifeLoss.setVolume((float)this->_soundVolume / 8);
}

void SFMainSoundPlayer::refreshAllMenuVolume(int globalVolume, int musicVolume, int soundVolume) {
    this->_globalVolume = globalVolume;
    this->_musicVolume = musicVolume;
    this->_soundVolume = soundVolume;
    this->_menuMusic.setVolume(musicVolume);
    this->_menuClick.setVolume(soundVolume);
    this->_menuClick.play();
    sf::Listener::setGlobalVolume(globalVolume);
}