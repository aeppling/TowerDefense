//
// Created by adrie on 12/04/2023.
//

#include "MissileLauncher.hpp"
#include "MissileThread.hpp"

MissileLauncher::MissileLauncher(SFMLMissileLoader &sfmlMissileLoader, int cellSize, std::string typeName)
                                : _sfmlMissileLoader(sfmlMissileLoader), _cellSize(cellSize), _typeName(typeName) {
}

MissileLauncher::~MissileLauncher() {
    std::lock_guard<std::mutex> lock(this->_missilesMutex);
    for (MissileThread *missile : this->_missiles)
        delete missile;
    this->_missiles.clear();
}

void MissileLauncher::shoot(int towerPosX, int towerPosY, TDUnit *target, float missileSpeed) {
    MissileThread *missile = new MissileThread;
    // startThread() before publishing the pointer, so the render thread never
    // sees a missile whose sprite has not been set up yet.
    missile->startThread(this->_sfmlMissileLoader, {(float)towerPosX, (float)towerPosY},
                         target->getSprite().getPosition(), this->_cellSize, missileSpeed, this->_typeName);
    std::lock_guard<std::mutex> lock(this->_missilesMutex);
    this->_missiles.push_back(missile);
}

void MissileLauncher::endFinishedThreads() {
    std::lock_guard<std::mutex> lock(this->_missilesMutex);
    std::size_t i = 0;
    while (i < this->_missiles.size()) {
        if (this->_missiles.at(i)->isArrived()) {
            // The old loop incremented i even after erasing, so it skipped the
            // element that shifted into this slot, and it never freed the
            // MissileThread -- one leak per shot.
            delete this->_missiles.at(i);
            this->_missiles.erase(this->_missiles.begin() + i);
        }
        else
            i++;
    }
}

int MissileLauncher::getTotalMissiles() {
    std::lock_guard<std::mutex> lock(this->_missilesMutex);
    return (this->_missiles.size());
}

sf::Sprite MissileLauncher::getSpriteByIndex(int index) {
    std::lock_guard<std::mutex> lock(this->_missilesMutex);
    // The render thread reads the count and the elements in separate calls, so
    // the list can shrink in between: return an off-screen sprite rather than
    // letting at() throw.
    if ((index < 0) || (index >= (int)this->_missiles.size())) {
        sf::Sprite empty;
        empty.setPosition(-5000, -5000);
        return (empty);
    }
    return (this->_missiles.at(index)->getSprite());
}

sf::Sprite MissileLauncher::getExplosionSpriteByIndex(int index) {
    std::lock_guard<std::mutex> lock(this->_missilesMutex);
    if ((index < 0) || (index >= (int)this->_missiles.size())) {
        sf::Sprite empty;
        empty.setPosition(-5000, -5000);
        return (empty);
    }
    return (this->_missiles.at(index)->getExplosionSprite());
}
