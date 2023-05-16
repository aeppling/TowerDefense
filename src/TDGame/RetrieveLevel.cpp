//
// Created by adrie on 20/03/2023.
//

#include <fstream>
#include "RetrieveLevel.hpp"
#include "../TDGraphics/SFMLLoaderPlanet1.hpp"
#include "../TDUnits/Drone.hpp"
#include "../TDUnits/Missile.hpp"
#include "../TDUnits/Alien.hpp"
#include "../TDUnits/Spaceship.hpp"
#include "../TDUnits/FlyingDrone.hpp"
#include "../TDUnits/RegenerateDrone.hpp"
#include "../TDUnits/ArmoredDrone.hpp"
#include "../TDUnits/ArmoredAlien.hpp"
#include "../TDUnits/ArmoredFlyingDrone.hpp"
#include "../TDUnits/ArmoredRegenerateDrone.hpp"
#include "../TDUnits/BossPlanet1.hpp"
#include "../TDUnits/BossPlanet2.hpp"
#include "../TDUnits/BossPlanet3.hpp"

RetrieveLevel::RetrieveLevel(int starting_level, int planet) : _actual_level(starting_level), _planet(planet) {
}

TDUnit *getUnitFromString(std::string enemyType) {
    TDUnit *newUnit;
    SFMLLoaderPlanet1 sfmlLoaderUnit;
    if (enemyType == "Drone")
        newUnit = new Drone(0, 0);
    else if (enemyType == "Missile")
        newUnit = new Missile(0, 0);
    else if (enemyType == "Spaceship")
        newUnit = new Spaceship(0, 0);
    else if (enemyType == "Alien")
        newUnit = new Alien(0, 0);
    else if (enemyType == "FlyingDrone")
        newUnit = new FlyingDrone(0, 0);
    else if (enemyType == "RegenerateDrone")
        newUnit = new RegenerateDrone(0, 0);
    else if (enemyType == "ArmoredDrone")
        newUnit = new ArmoredDrone(0, 0);
    else if (enemyType == "ArmoredAlien")
        newUnit = new ArmoredAlien(0, 0);
    else if (enemyType == "ArmoredFlyingDrone")
        newUnit = new ArmoredFlyingDrone(0, 0);
    else if (enemyType == "ArmoredRegenerateDrone")
        newUnit = new ArmoredRegenerateDrone(0, 0);
   /* else if (enemyType == "BossPlanet1")
        newUnit = new BossPlanet1(0, 0);
    else if (enemyType == "BossPlanet2")
        newUnit = new BossPlanet2(0, 0);
    else if (enemyType == "BossPlanet3")
        newUnit = new BossPlanet3(0, 0);*/
    else {
        std::cout << "Unknown unit named '" << enemyType << "'" << std::endl;
        return (nullptr);
    }
    return (newUnit);
}

std::vector<TDUnit*> RetrieveLevel::getWaveFromString(std::string waveString) {
    std::vector<TDUnit*> newWave;
    int separatorPos = waveString.find('/');;

    int i = 1;
    while (separatorPos != std::string::npos) {
        std::string enemyInfos = waveString.substr(0, separatorPos);
        std::string remaining = waveString.substr(separatorPos + 1);
        std::string enemyType = enemyInfos.substr(0, enemyInfos.find(':'));
        std::string enemyAmountString = enemyInfos.substr((enemyInfos.find(':') + 1), enemyInfos.length());
        int enemyAmount = stoi(enemyAmountString);
        int enemyIncr = 0;
        //UNCOMMENT TO DEBUG
        // std::cout << "TYPE=" << enemyType << "|AMOUNT=" << enemyAmount << "|" << std::endl;
        while (enemyIncr != enemyAmount) {
            newWave.push_back(getUnitFromString(enemyType));
            enemyIncr++;
        }
        waveString = remaining;
        separatorPos = waveString.find('/');
        i++;
    }
    std::string lastEnemy = waveString;
    std::string enemyType = lastEnemy.substr(0, lastEnemy.find(':'));
    std::string enemyAmountString = lastEnemy.substr((lastEnemy.find(':') + 1), lastEnemy.length());
    int enemyAmount = stoi(enemyAmountString);
    int enemyIncr = 0;
    //UNCOMMENT TO DEBUG
    //std::cout << "TYPE=" << enemyType << "|AMOUNT=" << enemyAmount << "|" << std::endl << std::endl;
    while (enemyIncr != enemyAmount) {
        newWave.push_back(getUnitFromString(enemyType));
        enemyIncr++;
    }
    return (newWave);
}

std::vector<std::vector<TDUnit*>> RetrieveLevel::getNextLevel() {
    std::string path_to_open("Planet_" + std::to_string(this->_planet) + "/level_" + std::to_string(this->_actual_level) + "_planet_" +  std::to_string(this->_planet) + ".txt");
    std::ifstream levelFile;
    std::vector<std::vector<TDUnit*>> enemyLevel;
    int i = 1;

    enemyLevel.empty();
    levelFile.open(path_to_open);
    if (levelFile.is_open()) {
        while (levelFile) {
            std::vector<TDUnit*> enemyWave;
            std::string nextLine;
            std::getline(levelFile, nextLine);
            if (nextLine.empty() == true)
                break;
            // UNCOMMENT TO DEBUG
            // std::cout << std::endl << "Wave " << i << " : " << nextLine << std::endl;
            enemyWave = getWaveFromString(nextLine);
            enemyLevel.push_back(enemyWave);
            i++;
        }
    }
    else {
        std::cout << "Error on file opening" << std::endl;
        return (enemyLevel);
    }
    return (enemyLevel);
}

RetrieveLevel::~RetrieveLevel() {
    
}

