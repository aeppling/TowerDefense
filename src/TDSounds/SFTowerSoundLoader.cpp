//
// Created by adrie on 06/05/2023.
//

#include <iostream>
#include "SFTowerSoundLoader.hpp"

SFTowerSoundLoader::SFTowerSoundLoader(unsigned int musicVolume, unsigned int soundVolume) {
    bool checkError = false;
    this->_musicVolume = musicVolume;
    this->_soundVolume = soundVolume;
    if (!(this->_basicShot.loadFromFile("ressources/Sounds/SingleShot2.wav")))
        checkError = true;
    if (!(this->_speedShot.loadFromFile("ressources/Sounds/DefiniteShot5.wav")))
        checkError = true;
    if (!(this->_antiAirShot.loadFromFile("ressources/Sounds/MissileLaunchMini2.wav")))
        checkError = true;
    if (!(this->_slowShot.loadFromFile("ressources/Sounds/SlowTowerShot.wav")))
        checkError = true;
    if (!(this->_sniperShot.loadFromFile("ressources/Sounds/SingleShot.wav")))
        checkError = true;
    if (!(this->_splashShot.loadFromFile("ressources/Sounds/SplashTowerShot.wav")))
        checkError = true;
    if (!(this->_enemyDeath.loadFromFile("ressources/Sounds/DestroyMonster2.wav")))
        checkError = true;
    if (checkError == true) {
        std::cout << "Error on loading tower sounds..." << std::endl;
        return ;
    }
}

sf::SoundBuffer *SFTowerSoundLoader::getFromName(std::string name) {
    if (name == "BasicTower")
        return (&this->_basicShot);
    if (name == "AttackSpeedTower")
        return (&this->_speedShot);
    if (name == "AntiAirTower")
        return (&this->_antiAirShot);
    if (name == "SlowTower")
        return (&this->_slowShot);
    if (name == "SniperTower")
        return (&this->_sniperShot);
    if (name == "SplashTower")
        return (&this->_splashShot);
    else
        return (&this->_basicShot);
}