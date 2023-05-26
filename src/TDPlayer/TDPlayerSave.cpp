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
    this->_unlockedLevelsPlanet1 = 10; //1
    this->_unlockedLevelsPlanet2 = 10; //0
    this->_unlockedLevelsPlanet3 = 10; //0
    this->_globalVolume = 100;
    this->_musicVolume = 100;
    this->_soundVolume = 100;
    this->_difficulty = 1;
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(this), sizeof(*this));
        file.close();
    }
}

void TDPlayerSave::loadPlayerData(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(this), sizeof(*this));
        file.close();
    }
}

void TDPlayerSave::debugDisplayPlayerInfos() {
    std::cout << "Unlocked (P1,P2,P3) : " << this->_unlockedLevelsPlanet1 << "," << this->_unlockedLevelsPlanet2 << ",";
    std::cout << this->_unlockedLevelsPlanet3 << std::endl;
    std::cout << "Volumes (Global,Music,Sound) : " << this->_globalVolume << "," << this->_musicVolume << ",";
    std::cout << this->_soundVolume << "," << std::endl;
    std::cout << "Difficulty : " << this->_difficulty << std::endl;
}