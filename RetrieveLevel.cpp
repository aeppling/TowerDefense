//
// Created by adrie on 20/03/2023.
//

#include <fstream>
#include "RetrieveLevel.hpp"

RetrieveLevel::RetrieveLevel(int starting_level) : _actual_level(starting_level) {
}

TDUnit *getUnitFromString(std::string enemyType) {
    TDUnit *newUnit;

    if (enemyType == "Cowards")
        newUnit = new Cowards(0, 0);
    else if (enemyType == "Minions")
        newUnit = new Minions(0, 0);
    else if (enemyType == "Bats")
        newUnit = new Bats(0, 0);
    else if (enemyType == "Dragon")
        newUnit = new Dragon(0, 0);
    else if (enemyType == "Molosse")
        newUnit = new Molosse(0, 0);
    else if (enemyType == "Golem")
        newUnit = new Golem(0, 0);
    else if (enemyType == "Goblin")
        newUnit = new Goblin(0, 0);
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
    std::string path_to_open("level_" + std::to_string(this->_actual_level) + ".txt");
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

