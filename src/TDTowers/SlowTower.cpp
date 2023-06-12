#include <mutex>
#include "SlowTower.hpp"

std::mutex slow_mtx;

SlowTower::SlowTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, SFTowerSoundLoader &soundLoader): Tower(gameInstance, 3, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "SlowTower",
                                                                                                                                                                      {1500, 2250, 3000}, {350, 500, 650}, {7, 7, 8}, {5, 5, 5}, 4, false, soundLoader){
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
        this->missileLauncher->shoot(this->towerSprite.getPosition().x, this->towerSprite.getPosition().y, target, this->missileSpeed);
        target->getFreeze((float)this->damage[this->level]);
        if (this->enemiesInRange.size() >= 2) {
            this->removeFromEnemiesInRangeList(target);
        }
    } catch (const std::system_error& ex) {
        std::cerr << "Caught std::system_error exception: " << ex.what() << std::endl;
    }
    this->missileLauncher->endFinishedThreads();
    slow_mtx.unlock();
}
