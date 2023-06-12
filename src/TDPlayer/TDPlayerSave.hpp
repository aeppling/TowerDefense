//
// Created by adrie on 12/05/2023.
//

#ifndef UNTITLED1_TDPLAYERSAVE_HPP
#define UNTITLED1_TDPLAYERSAVE_HPP

#include <string>

class TDPlayerSave {
private:
    int     _unlockedLevelsPlanet1;
    int     _unlockedLevelsPlanet2;
    int     _unlockedLevelsPlanet3;
    int     _globalVolume;
    int     _musicVolume;
    int     _soundVolume;
    int     _difficulty;
public:
    TDPlayerSave(std::string filename);
    ~TDPlayerSave() {};

    // INIT / SAVE / LOAD
    void initPlayerData(const std::string& filename);
    void savePlayerData(const std::string& filename);
    void loadPlayerData(const std::string& filename);

    // GETTERS
    int getUnlockedPlanet1() { return(this->_unlockedLevelsPlanet1); };
    int getUnlockedPlanet2() { return(this->_unlockedLevelsPlanet2); };
    int getUnlockedPlanet3() { return(this->_unlockedLevelsPlanet3); };

    int getGlobalVolume() { return(this->_globalVolume); };
    int getMusicVolume() { return(this->_musicVolume); };
    int getSoundVolume() { return(this->_soundVolume); };

    int getDifficulty() { return(this->_difficulty); };
    // SETTER & UNLOCKER
    void unlockPlanet1Level() {
        if (this->_unlockedLevelsPlanet1 >= 10) {
            if (this->_unlockedLevelsPlanet2 == 0)
                this->_unlockedLevelsPlanet2++;
            else
                return;
        }
        else
            this->_unlockedLevelsPlanet1++;
    };
    void unlockPlanet2Level() {
        if (this->_unlockedLevelsPlanet2 >= 10) {
            if (this->_unlockedLevelsPlanet3 == 0)
                this->_unlockedLevelsPlanet3++;
            else
                return;
        }
        else
            this->_unlockedLevelsPlanet2++;
    };
    void unlockPlanet3Level() {
        if (this->_unlockedLevelsPlanet3 >= 10)
                return;
        else
            this->_unlockedLevelsPlanet3++;
    };

    void setGlobalVolume(int globalVolume) { this->_globalVolume = globalVolume; };
    void setMusicVolume(int musicVolume) { this->_musicVolume = musicVolume; };
    void setSoundVolume(int soundVolume) { this->_soundVolume = soundVolume; };
    void setDifficulty(int difficulty) { this->_difficulty = difficulty; };
    // DEBUG
    void debugDisplayPlayerInfos();
};

#endif //UNTITLED1_TDPLAYERSAVE_HPP
