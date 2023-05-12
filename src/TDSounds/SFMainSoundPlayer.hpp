//
// Created by adrie on 02/05/2023.
//

#ifndef UNTITLED1_SFMAINSOUNDPLAYER_HPP
#define UNTITLED1_SFMAINSOUNDPLAYER_HPP

#include "../TDSounds/SFMainSoundLoader.hpp"

class SFMainSoundPlayer {
private:
    unsigned int _musicVolume;
    unsigned int _soundVolume;
    unsigned int _globalVolume;
    // MUSIC
    sf::Music _menuMusic;
    sf::Music _gameMusic1;
    sf::Music _gameMusic2;
    sf::Music _gameMusicChill;
    sf::Music _gameMusicEndWave;
    sf::Music _gameMusicFaster;

    //SOUNDS
    sf::Sound _menuClick;
    sf::Sound _gamePlacementClick;
    sf::Sound _gameCoinWon;
    sf::Sound _waveClear;
    sf::Sound _gameCoinLoss;
    sf::Sound _gameLifeLoss;
    sf::Sound _gameSellObject;
public:
    SFMainSoundPlayer(SFMainSoundLoader &soundLoader, unsigned int globalVolume, unsigned int musicVolume, unsigned int soundVolume);
    ~SFMainSoundPlayer() {};

    // GETTER VOLUME
    unsigned int getMusicVolume() { return (this->_musicVolume); };
    unsigned int getSoundVolume() { return (this->_soundVolume); };

    // SETTER VOLUME
    void refreshAllMenuVolume(int globalVolume, int musicVolume, int soundVolume);
    // MUSIC
    void playMenuMusic() { this->_menuMusic.play(); };
    void stopMenuMusic() { this->_menuMusic.stop(); };
    void playGameMusic1() { this->_gameMusic1.play(); };
    void playGameMusic2() { this->_gameMusic2.play(); };
    void playGameMusicChill() { this->_gameMusicChill.play(); };
    void playGameMusicEndWave() { this->_gameMusicEndWave.play(); };
    void playGameMusicFaster() { this->_gameMusicFaster.play(); };
    void stopGameMusic() { this->_gameMusic1.stop(); this->_gameMusic2.stop(); this->_gameMusicChill.stop();
        this->_gameMusicEndWave.stop(); this->_gameMusicFaster.stop();};

    // SOUNDS
    void playMenuClick() { this->_menuClick.play(); };
    void playGamePlacementClick() { this->_gamePlacementClick.play(); };
    void playGameCoinWon() { this->_gameCoinWon.play(); };
    void playWaveClear() { this->_waveClear.play(); };
    void playGameCoinLoss() { this->_gameCoinLoss.play(); };
    void playLifeLoss() { this->_gameLifeLoss.play(); };
};
#endif //UNTITLED1_SFMAINSOUNDPLAYER_HPP
