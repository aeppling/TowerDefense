//
// Created by adrie on 09/05/2023.
//

#include "SpeedAuraTower.hpp"
#include <mutex>

std::mutex mtx_aura;

SpeedAuraTower::SpeedAuraTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, SFTowerSoundLoader &soundLoader): Tower(gameInstance, 3, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "SpeedAuraTower",
                                                                                                                                                                                                   {10, 25, 40}, {450, 650, 800}, {10, 12, 14}, {1.5, 1.3, 1.2}, 5, false, soundLoader){
}

void SpeedAuraTower::removeFromTowerInRangeList(Tower *tower){
    //* Remove enemy from enemies in range vector
    this->_towerInRange.erase(std::remove(this->_towerInRange.begin(), this->_towerInRange.end(), tower), this->_towerInRange.end());
}

void SpeedAuraTower::addToTowerInRangeList(Tower *tower){
    //* Add enemy to enemies in range vector
    this->_towerInRange.push_back(tower);
}

void SpeedAuraTower::isInRange() {
    //   this->enemiesInRange.push_back(enemiesList[0]);
    //* if enemy is in the tower's range add him to the vector, if he isnt, remove him
    for (Tower *tower: *(this->_towerList)) {
        mtx_aura.lock();
        if ((tower->getPosition().x <= this->coord.x + this->range.at(this->level) + this->getSize() &&
                tower->getPosition().x >= this->coord.x - this->range.at(this->level) &&
                tower->getPosition().y <= this->coord.y + this->range.at(this->level) + this->getSize() &&
                tower->getPosition().y >= this->coord.y - this->range.at(this->level))){
            if (std::find(this->_towerInRange.begin(), this->_towerInRange.end(), tower) ==
                    this->_towerInRange.end()) {
                addToTowerInRangeList(tower);
            }
        } else {
            if (std::find(this->_towerInRange.begin(), this->_towerInRange.end(), tower) !=
                    this->_towerInRange.end()) {
                removeFromTowerInRangeList(tower);
            }

        }
        mtx_aura.unlock();
    }
}

void SpeedAuraTower::live(std::vector<Tower*> *towerList) {
    this->activate(towerList);
}

void SpeedAuraTower::run(std::vector<Tower*> *towerList){
    //* run the tower threadst
    this->gameInstance->getCurrentWaveNumber();
    this->_towerThread = std::thread(&SpeedAuraTower::live, this, towerList);
}

void SpeedAuraTower::activate(std::vector<Tower*> *towerList){
    this->_towerList = towerList;
    this->activated = true;

    while (this->activated) {
        if (this->activated == false)
            break;
        this->isInRange();
        if (this->_towerInRange.size() > 0) {
            this->setSpeedTowerBuff();
        }
        sf::sleep(sf::milliseconds(500));
    }
}
void SpeedAuraTower::deactivate(){
    //  if (this->_towerThread.joinable())
    //    this->_towerThread.join();
    this->resetAllBuff();
    this->activated = false;
    this->_towerInRange.clear();
    this->enemiesList->clear();
    this->enemiesInRange.clear();
}

void SpeedAuraTower::setSpeedTowerBuff() {
    int i = 0;

    while (i < this->_towerInRange.size()) {
        if (this->_towerInRange.at(i)->isSpeedBoosted() == false || (((1.0f - this->_towerInRange.at(i)->getSpeedBuff()) * 100) < (float)this->damage[this->level])) {
            this->_towerInRange.at(i)->setSpeedBuffValue(this->damage[this->level]);
        }
        i++;
    }
}

void SpeedAuraTower::resetAllBuff() {
    int i = 0;

    while (i < this->_towerInRange.size()) {
        if (this->_towerInRange.at(i)->isSpeedBoosted() == true) {
            this->_towerInRange.at(i)->resetSpeedBuff();
            this->_towerInRange.at(i)->setSpeedBoosted(false);
        }
        i++;
    }
}