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
    if (!(this->_menuMusic.openFromFile("ressources/Music/menu_music.ogg")))
        checkError = true;
    if (!(this->_gameMusic1.openFromFile("ressources/Music/game_music1.ogg")))
        checkError = true;
    if (!(this->_gameMusic2.openFromFile("ressources/Music/game_music2.ogg")))
        checkError = true;
    if (!(this->_gameMusicChill.openFromFile("ressources/Music/game_music_chill.ogg")))
        checkError = true;
    if (!(this->_gameMusicEndWave.openFromFile("ressources/Music/game_music_endwave.ogg")))
        checkError = true;
    if (!(this->_gameMusicFaster.openFromFile("ressources/Music/game_music_faster.ogg")))
        checkError = true;
    if (checkError == true) {
        std::cout << "Error on loading main sounds..." << std::endl;
        return ;
    }

    sf::Listener::setGlobalVolume((float)this->_globalVolume);

    // Loop every track. Nothing in the project called setLoop(), so each piece
    // played through once and then stopped for good -- the game music only got
    // a chance to restart between two waves, leaving long silences mid-wave.
    this->_menuMusic.setLoop(true);
    this->_gameMusic1.setLoop(true);
    this->_gameMusic2.setLoop(true);
    this->_gameMusicChill.setLoop(true);
    this->_gameMusicEndWave.setLoop(true);
    this->_gameMusicFaster.setLoop(true);

    this->_menuMusic.setVolume((float)this->_musicVolume);
    this->_gameMusic1.setVolume((float)this->_musicVolume * 1.2);
    this->_gameMusic2.setVolume((float)this->_musicVolume * 1.4);
    this->_gameMusicChill.setVolume((float)this->_musicVolume);
    this->_gameMusicEndWave.setVolume((float)this->_musicVolume * 2);
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
    // No play() here. This is a volume setter, and main.cpp already plays the
    // click on MouseButtonPressed; this ran on MouseButtonReleased, so every
    // single click inside the settings menu was heard twice. It also fired once
    // at start-up, clicking on its own before the player touched anything.
    sf::Listener::setGlobalVolume(globalVolume);
}

void SFMainSoundPlayer::pauseGameMusic() {
    if (this->_gameMusic1.getStatus() == sf::Music::Playing)
        this->_gameMusic1.pause();
    if (this->_gameMusic2.getStatus() == sf::Music::Playing)
        this->_gameMusic2.pause();
    if (this->_gameMusicChill.getStatus() == sf::Music::Playing)
        this->_gameMusicChill.pause();
    if (this->_gameMusicEndWave.getStatus() == sf::Music::Playing)
        this->_gameMusicEndWave.pause();
    if (this->_gameMusicFaster.getStatus() == sf::Music::Playing)
        this->_gameMusicFaster.pause();
}

void SFMainSoundPlayer::resumeGameMusic() {
    // play() on a paused stream resumes from where it stopped; on a stopped one
    // it would restart from the beginning, so only touch the paused tracks.
    if (this->_gameMusic1.getStatus() == sf::Music::Paused)
        this->_gameMusic1.play();
    if (this->_gameMusic2.getStatus() == sf::Music::Paused)
        this->_gameMusic2.play();
    if (this->_gameMusicChill.getStatus() == sf::Music::Paused)
        this->_gameMusicChill.play();
    if (this->_gameMusicEndWave.getStatus() == sf::Music::Paused)
        this->_gameMusicEndWave.play();
    if (this->_gameMusicFaster.getStatus() == sf::Music::Paused)
        this->_gameMusicFaster.play();
}

bool SFMainSoundPlayer::isAnyGameMusicPlaying() {
    return ((this->_gameMusic1.getStatus() == sf::Music::Playing)
            || (this->_gameMusic2.getStatus() == sf::Music::Playing)
            || (this->_gameMusicChill.getStatus() == sf::Music::Playing)
            || (this->_gameMusicEndWave.getStatus() == sf::Music::Playing)
            || (this->_gameMusicFaster.getStatus() == sf::Music::Playing));
}

void SFMainSoundPlayer::checkForGameMusicToReplay() {
    // Only look at _gameMusic1 before, so on the final wave -- where the caller
    // stops everything and starts _gameMusicFaster -- this saw _gameMusic1
    // stopped and layered it on top, playing two tracks at once.
    if (!this->isAnyGameMusicPlaying())
        this->_gameMusic1.play();
}

void SFMainSoundPlayer::checkForMenuMusicToReplay() {
    if (this->_menuMusic.getStatus() == sf::Music::Stopped)
        this->_menuMusic.play();
}