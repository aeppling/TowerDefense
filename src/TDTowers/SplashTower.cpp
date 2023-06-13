#include "SplashTower.hpp"
#include <mutex>

std::mutex mtx_tow;

SplashTower::SplashTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, SFTowerSoundLoader &soundLoader): Tower(gameInstance, 3, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "SplashTower",
                                                                                                                                                                              {15, 25, 35}, {500, 700, 1000}, {10, 12, 14}, {3, 2.5, 2}, 6.5, false, soundLoader){
}

void SplashTower::fire(TDUnit *target){
    if (this->enemiesInRange.size() >= 3) {
        try {
            mtx_tow.lock();
            this->_shotSound.play();
            int i = 0;
            while (i < this->enemiesInRange.size()) {
                target = this->enemiesInRange.at(i);
                if (target->_isKilled == true) {
                    removeFromEnemiesInRangeList(target);
                    continue;
                }
                this->missileLauncher->shoot(this->towerSprite.getPosition().x, this->towerSprite.getPosition().y, target, this->missileSpeed);
                target->getShot(this->damage[this->level], 0, this->armorPierceValue);
                if (target->getHealth() <= 0) {
                    //  this->gameInstance.addCoins(target->getValue());
                    this->_killSound.play();
                    removeFromEnemiesInRangeList(target);
                    this->enemiesList->erase(std::remove(this->enemiesList->begin(), this->enemiesList->end(), target),
                                             this->enemiesList->end());
                    target->getKill();

                }
                i++;
            }
            mtx_tow.unlock();
        } catch (const std::system_error &ex) {
            std::cerr << "Caught std::system_error exception: " << ex.what() << std::endl;
            // Additional error handling or recovery logic
        }
        this->missileLauncher->endFinishedThreads();
    }
}
