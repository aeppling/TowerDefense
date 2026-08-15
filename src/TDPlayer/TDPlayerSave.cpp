//
// Created by adrie on 12/05/2023.
//

#include <fstream>
#include <iostream>
#include "TDPlayerSave.hpp"

TDPlayerSave::TDPlayerSave(std::string filename) {
    // IF FILE EXIST, RETRIEVE, ELSE SET DEFAULT
    std::ifstream file;
    file.open(filename);
    if (file)
        this->loadPlayerData(filename);
    else
        this->initPlayerData(filename);
}

void TDPlayerSave::savePlayerData(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(this), sizeof(*this));
        file.close();
    }
}

void TDPlayerSave::initPlayerData(const std::string& filename) {
    // Debug values (10/10/10) were left in: a fresh install had every level
    // unlocked, contradicting the README. Restored to the intended defaults
    // written in the trailing comments.
    this->_unlockedLevelsPlanet1 = 1;
    this->_unlockedLevelsPlanet2 = 0;
    this->_unlockedLevelsPlanet3 = 0;
    this->_globalVolume = 100;
    this->_musicVolume = 100;
    this->_soundVolume = 100;
    this->_difficulty = 2;
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(this), sizeof(*this));
        file.close();
    }
}

void TDPlayerSave::loadPlayerData(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        this->initPlayerData(filename);
        return;
    }
    file.read(reinterpret_cast<char*>(this), sizeof(*this));
    // A short read used to leave every field uninitialised: garbage volume,
    // garbage unlocked-level counts. Fall back to defaults instead.
    if (file.gcount() != (std::streamsize)sizeof(*this)) {
        file.close();
        std::cout << "Corrupt save file, resetting to defaults." << std::endl;
        this->initPlayerData(filename);
        return;
    }
    file.close();
    // Clamp anything out of range so a hand-edited or partially written file
    // cannot feed absurd values into the menus.
    if ((this->_unlockedLevelsPlanet1 < 1) || (this->_unlockedLevelsPlanet1 > 10))
        this->_unlockedLevelsPlanet1 = 1;
    if ((this->_unlockedLevelsPlanet2 < 0) || (this->_unlockedLevelsPlanet2 > 10))
        this->_unlockedLevelsPlanet2 = 0;
    if ((this->_unlockedLevelsPlanet3 < 0) || (this->_unlockedLevelsPlanet3 > 10))
        this->_unlockedLevelsPlanet3 = 0;
    if ((this->_globalVolume < 0) || (this->_globalVolume > 100))
        this->_globalVolume = 100;
    if ((this->_musicVolume < 0) || (this->_musicVolume > 100))
        this->_musicVolume = 100;
    if ((this->_soundVolume < 0) || (this->_soundVolume > 100))
        this->_soundVolume = 100;
    if ((this->_difficulty < 1) || (this->_difficulty > 3))
        this->_difficulty = 2;
}

void TDPlayerSave::debugDisplayPlayerInfos() {
    std::cout << "Unlocked (P1,P2,P3) : " << this->_unlockedLevelsPlanet1 << "," << this->_unlockedLevelsPlanet2 << ",";
    std::cout << this->_unlockedLevelsPlanet3 << std::endl;
    std::cout << "Volumes (Global,Music,Sound) : " << this->_globalVolume << "," << this->_musicVolume << ",";
    std::cout << this->_soundVolume << "," << std::endl;
    std::cout << "Difficulty : " << this->_difficulty << std::endl;
}