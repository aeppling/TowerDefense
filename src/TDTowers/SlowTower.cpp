#include <mutex>
#include "SlowTower.hpp"

std::mutex slow_mtx;

SlowTower::SlowTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, SFTowerSoundLoader &soundLoader): Tower(gameInstance, 3, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "SlowTower",
                                                                                                                                                                      {2000, 2750, 3500}, {400, 550, 700}, {8, 9, 10}, {5, 5, 5}, 4, false, soundLoader){
}

void SlowTower::fire(TDUnit *target){
    if (target->_isKilled == true) {
        removeFromEnemiesInRangeList(target);
        return ;
    }
    this->rotate(target);
    try  {
        slow_mtx.lock();
        std::thread animationThread(&Tower::animateFiring, this);
        animationThread.detach();
        this->_shotSound.play();
        // JUST REMOVE ANIMATION FROM GET SHOT
        //std::thread shotThread(&TDUnit::getShot, target, this->damage[this->level], 0);
        //shotThread.detach();
        this->missileLauncher->shoot(this->towerSprite.getPosition().x, this->towerSprite.getPosition().y, target, this->missileSpeed);
        target->getFreeze((float)this->damage[this->level]);
        if (this->enemiesInRange.size() >= 2) {
            this->removeFromEnemiesInRangeList(target);
        }
        //shotThread.join();
        if (target->getHealth() <= 0) {
            this->_killSound.play();
            removeFromEnemiesInRangeList(target);
            this->enemiesList->erase(std::remove(this->enemiesList->begin(), this->enemiesList->end(), target), this->enemiesList->end());
            target->getKill();
        }
    } catch (const std::system_error& ex) {
        std::cerr << "Caught std::system_error exception: " << ex.what() << std::endl;
    }
    this->missileLauncher->endFinishedThreads();
    slow_mtx.unlock();
}
