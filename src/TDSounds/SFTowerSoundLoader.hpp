//
// Created by adrie on 06/05/2023.
//

#ifndef UNTITLED1_SFTOWERSOUNDLOADER_HPP
#define UNTITLED1_SFTOWERSOUNDLOADER_HPP

#include "SFML/Audio.hpp"

class SFTowerSoundLoader {
private:
    unsigned int _musicVolume;
    unsigned int _soundVolume;

    sf::SoundBuffer _basicShot;
    sf::SoundBuffer _speedShot;
    sf::SoundBuffer _antiAirShot;
    sf::SoundBuffer _slowShot;
    sf::SoundBuffer _sniperShot;
    sf::SoundBuffer _splashShot;
public:
    SFTowerSoundLoader(unsigned int musicVolume, unsigned int soundVolume);
    ~SFTowerSoundLoader() = default;

    unsigned int getMusicVolume() { return (this->_musicVolume); };
    unsigned int getSoundVolume() { return (this->_soundVolume); };

    sf::SoundBuffer *getFromName(std::string name);
    sf::SoundBuffer *getBasicShot() { return (&this->_basicShot); };
    sf::SoundBuffer *getSpeedShot() { return (&this->_speedShot); };
    sf::SoundBuffer *getAntiAirShot() { return (&this->_antiAirShot); };
    sf::SoundBuffer *getSlowShot() { return (&this->_slowShot); };
    sf::SoundBuffer *getSniperShot() { return (&this->_sniperShot); };
    sf::SoundBuffer *getSplashShot() { return (&this->_splashShot); };
};

#endif //UNTITLED1_SFTOWERSOUNDLOADER_HPP
