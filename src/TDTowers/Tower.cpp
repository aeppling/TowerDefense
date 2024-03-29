#include <unistd.h>
#include <mutex>
#include <math.h>
#include "Tower.hpp"
#include "../TDGraphics/SFMLMissileLoader.hpp"
#include "../TDGame/usefullStruct.hpp"

std::mutex mtx;

Tower::Tower(Game *gameInstance, int size, int cellSize, SFMLTowerLoader &sfmlLoaderTower, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, std::string towerName,
             std::vector<int> damage, std::vector<int> cost, std::vector<float> range, std::vector<float> timeBetweenAttack, float missileSpeed, bool isAerial, SFTowerSoundLoader &soundLoader) : window(window), Buildable(size, "Tower") {
    this->isPlaced = false;
    this->towerName = towerName;
    this->isPaused = false;
    if (this->towerName == "BasicTower")
        this->towerSprite.setTexture(*sfmlLoaderTower.getBasic());
    else if (this->towerName == "AntiAirTower")
        this->towerSprite.setTexture(*sfmlLoaderTower.getAntiAir());
    else if (this->towerName == "AttackSpeedTower")
        this->towerSprite.setTexture(*sfmlLoaderTower.getSpeed());
    else if (this->towerName == "SlowTower")
        this->towerSprite.setTexture(*sfmlLoaderTower.getSlow());
    else if (this->towerName == "SniperTower")
        this->towerSprite.setTexture(*sfmlLoaderTower.getSniper());
    else if (this->towerName == "SplashTower")
        this->towerSprite.setTexture(*sfmlLoaderTower.getSplash());
    else if (this->towerName == "SpeedAuraTower")
        this->towerSprite.setTexture(*sfmlLoaderTower.getAura());
    else {
        std::cout << "Tower name not found ... Cannot add to shop." << std::endl;
        return ;
    }
    this->_shotSound.setBuffer(*soundLoader.getFromName(this->towerName));
    this->_shotSound.setVolume((float)soundLoader.getSoundVolume() / 10);
    this->_killSound.setBuffer(*soundLoader.getEnemyDeath());
    this->_killSound.setVolume((float)soundLoader.getSoundVolume() / 14);
    this->missileSpeed = missileSpeed;
    this->missileLauncher = new MissileLauncher(sfmlMissileLoader, cellSize, this->towerName);
    float scaleFactor = static_cast<float>(cellSize) / static_cast<float>(this->towerSprite.getTexture()->getSize().y);
    sf::IntRect textureRect(0, 0, this->towerSprite.getTexture()->getSize().y, this->towerSprite.getTexture()->getSize().y);
    if ((this->towerName == "SlowTower") || (this->towerName == "SplashTower"))
        this->towerSprite.setScale(scaleFactor * 2.5, scaleFactor * 2.5);
    else if ((this->towerName == "SniperTower") || (this->towerName == "AntiAirTower"))
        this->towerSprite.setScale(scaleFactor * 3.8, scaleFactor * 3.8);
    else if (this->towerName == "SpeedAuraTower")
        this->towerSprite.setScale(scaleFactor * 3.8, scaleFactor * 3.8);
    else
        this->towerSprite.setScale(scaleFactor * 4.5, scaleFactor * 4.5);
    this->towerSprite.setTextureRect(textureRect);
    if (this->towerName == "SniperTower") {
        sf::Vector2f newOrigin(this->towerSprite.getLocalBounds().width / 4.f,
                               this->towerSprite.getLocalBounds().height / 2.f);
        this->towerSprite.setOrigin(newOrigin);
    }
    else {
        sf::Vector2f newOrigin(this->towerSprite.getLocalBounds().width / 2.f,
                               this->towerSprite.getLocalBounds().height / 2.f);
        this->towerSprite.setOrigin(newOrigin);
    }
    this->_timeOfLastShot = std::chrono::steady_clock::now();
    this->gameInstance = gameInstance;
    this->level = 0;
    this->coord = {0, 0};
    this->damage = damage;
    this->cost = cost;
    this->range = range;
    this->slowValue = {50, 150, 300};
    this->timeBetweenAttack = timeBetweenAttack;
    this->activated = true;
    this->aerial = isAerial;
    this->speedBoosted = false;
    this->speedBuff = 1;
    this->armorPierceValue = 0;
}

void Tower::live(std::shared_ptr<std::vector<TDUnit*>> levelEnemyList) {
    this->activate(levelEnemyList);
}

void Tower::run(std::shared_ptr<std::vector<TDUnit*>> enemiesList){
    //* run the tower threadst
    this->gameInstance->getCurrentWaveNumber();
    this->_towerThread = std::thread(&Tower::live, this, enemiesList);
}

void Tower::removeFromEnemiesInRangeList(TDUnit *enemy){
    //* Remove enemy from enemies in range vector
    this->enemiesInRange.erase(std::remove(enemiesInRange.begin(), enemiesInRange.end(), enemy), enemiesInRange.end());
}

void Tower::addToEnemiesInRangeList(TDUnit *enemy){
    //* Add enemy to enemies in range vector
    this->enemiesInRange.push_back(enemy);
}

void Tower::setCurrentWave(std::shared_ptr<std::vector<TDUnit *>> enemiesList) {
    this->enemiesList = enemiesList;
}
/*bool Tower::isAlreadyInList() {

}*/


void Tower::isInRange() {
    int towerX = this->coord.x;
    int towerY = this->coord.y;
    int radius = this->range.at(this->level) + this->getSize();

    for (TDUnit* enemy : *(this->enemiesList)) {
        mtx.lock();
        int enemyX = enemy->getPosX();
        int enemyY = enemy->getPosY();

        // Calculate the distance between the tower and the enemy
        int distance = std::abs(enemyX - towerX) + std::abs(enemyY - towerY);

        // Check if the enemy is within the circular range
        if (distance <= radius && !(((enemy->isFlying() == true) && (this->aerial == false)) || ((enemy->isFlying() == false) && (this->aerial == true)))) {
            if (std::find(this->enemiesInRange.begin(), this->enemiesInRange.end(), enemy) == this->enemiesInRange.end()) {
                addToEnemiesInRangeList(enemy);
            }
        } else {
            if (std::find(this->enemiesInRange.begin(), this->enemiesInRange.end(), enemy) != this->enemiesInRange.end()) {
                removeFromEnemiesInRangeList(enemy);
            }
        }
        mtx.unlock();
    }
}

void Tower::activate(std::shared_ptr<std::vector<TDUnit*>> enemiesList){
    this->enemiesList = enemiesList;
    this->activated = true;
        while (this->activated) {
            if (this->activated == false)
                break;
            isInRange();
            if (enemiesInRange.size() > 0 && this->damage[this->level] > 0) {
                if (this->isPaused) {
                    while (this->isPaused)
                        sf::sleep(sf::milliseconds(50));
                }
                std::chrono::steady_clock::time_point testTime = std::chrono::steady_clock::now();
                int res = std::chrono::duration_cast<std::chrono::milliseconds>(
                        testTime - this->_timeOfLastShot).count();
                if (!this->enemiesInRange.empty() && (this->towerName != "SplashTower"))
                    this->rotate(this->enemiesInRange.at(0));
                if (res >= (this->timeBetweenAttack.at(this->level) * this->speedBuff) * 1000) {
                    if (!this->enemiesInRange.empty()) {
                        if (this->enemiesInRange.at(0)->alreadyArrived() || this->enemiesInRange.at(0)->alreadyCounted())
                            this->enemiesInRange.erase(this->enemiesInRange.begin());
                        if (!this->enemiesInRange.empty()) {
                            this->fire(this->enemiesInRange.at(0));
                            this->_timeOfLastShot = std::chrono::steady_clock::now();
                        }
                    }
                }
            }
        }
}

void Tower::sold() {
    this->activated = false;
}

void Tower::deactivate(){
    //* Deactivate the tower
    //if (this->_towerThread.joinable())
    //    this->_towerThread.join();
    this->activated = false;
    this->enemiesList->clear();
    this->enemiesInRange.clear();
}

bool Tower::isActivated() {
    return (this->activated);
}
void Tower::join() {
    if (this->_towerThread.joinable()) {
        this->_towerThread.join();
    }
   // this->enemiesList.reset();
   // this->enemiesList = nullptr;
}

void Tower::rotate(TDUnit *target) {
    sf::Vector2f towerPos = this->towerSprite.getPosition();
    sf::Vector2f targetPos = target->getSprite().getPosition();
    sf::Vector2f direction = targetPos - towerPos;
    float angle = atan2(direction.y, direction.x) * 180 / 3.14159f;
    this->towerSprite.setRotation(angle + 90);
}

void Tower::animateFiring() {
    float animationTime = 0.0f;
    float animationSpeed = 0.1f; // ANIMATION SPEED
    int numSprites = this->towerSprite.getTexture()->getSize().x / this->towerSprite.getTexture()->getSize().y;
    int spriteWidth = this->towerSprite.getTexture()->getSize().y;
    animationTime += animationSpeed;
    sf::IntRect textureRect(0, 0, 128, 128);
    this->towerSprite.setTextureRect(textureRect);

    int displayedSprite = 0;
    // Check if animation time exceeds the time for one sprite
    while (displayedSprite != numSprites) {
        textureRect.left += spriteWidth;
        this->towerSprite.setTextureRect(textureRect);
        displayedSprite++;
        if (displayedSprite != numSprites)
            sf::sleep(sf::milliseconds(20));
    }
    textureRect.left = 0;
    this->towerSprite.setTextureRect(textureRect);
}

void Tower::fire(TDUnit *target){
    if (target->_isKilled == true) {
        removeFromEnemiesInRangeList(target);
        return ;
    }
    this->rotate(target);
    try  {
        mtx.lock();
        std::thread animationThread(&Tower::animateFiring, this);
        animationThread.detach();
        this->_shotSound.play();
        // JUST REMOVE ANIMATION FROM GET SHOT
        //std::thread shotThread(&TDUnit::getShot, target, this->damage[this->level], 0);
        //shotThread.detach();
        this->missileLauncher->shoot(this->towerSprite.getPosition().x, this->towerSprite.getPosition().y, target, this->missileSpeed);
        target->getShot(this->damage[this->level], 0, this->armorPierceValue);
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
    mtx.unlock();
}

void Tower::upgrade(SFMLTowerLoader &sfmlTowerLoader){
    if(!this->isMaxed()){
        this->level++;
        this->towerSprite.setTexture(*sfmlTowerLoader.getTextureFromName(this->towerName, this->level));
    }
}

//* getters | setters

int Tower::getDamage(){
    return (this->damage[this->level]);
}
float Tower::getTimeBetweenAttack(){
    return (this->timeBetweenAttack.at(this->level));
}
void Tower::setTimeBetweenAttack(float time){
    this->timeBetweenAttack.at(this->level) = time;
}

bool Tower::isSpeedBoosted(){
    return (this->speedBoosted);
}

void Tower::setSpeedBoosted(bool newSpeedBoosted){
    this->speedBoosted = newSpeedBoosted;
}

int Tower::getCost(){
    return (this->cost[this->level]);
}
int Tower::getLevel(){
    return (this->level);
}

int Tower::getRange() {
    return (this->range.at(this->level));
}

void Tower::setPosition(int newXPos, int newYPos, int cellSize){
    this->coord = {newXPos,newYPos};
    this->towerSprite.setPosition((newXPos * cellSize) + cellSize/2 + _GAME_POSITION_X, ((newYPos * cellSize) + cellSize/2) + _GAME_POSITION_Y);
}

Point Tower::getPosition(){
    return (this->coord);
}

std::string Tower::getTowerName() { return (this->towerName); };

sf::Sprite Tower::getMissileSprite(int index) {
    return (this->missileLauncher->getSpriteByIndex(index));
}

sf::Sprite Tower::getExplosionSprite(int index) {
    return (this->missileLauncher->getExplosionSpriteByIndex(index));
}

int Tower::getTotalMissiles() {
    return (this->missileLauncher->getTotalMissiles());
}

bool Tower::isMaxed(){
    if (this->level + 1 < this->cost.size()) {
        return false;
    } else {
        return true;
    }

}

int Tower::getUpgradeCost(){
    if(this->isMaxed()){
        return -1;
    }
    return (this->cost[this->level+1]);
}

int Tower::getUpgradeDamage(){
    if(this->isMaxed()){
        return -1;
    }
    return (this->damage[this->level+1]);
}

int Tower::getUpgradeRange(){
    if(this->isMaxed()){
        return -1;
    }
    return (this->range[this->level+1]);
}

int Tower::getUpgradeAttackSpeed(){
    if(this->isMaxed()){
        return -1;
    }
    return (this->timeBetweenAttack[this->level+1]);
}

void Tower::setSpeedBuffValue(int value) {
    this->setSpeedBoosted(true);
    float bonusPercentage = static_cast<float>(value) / 100.0f;

    // Apply the bonus percentage to the attack speed
    float newSpeed = this->timeBetweenAttack[this->level] * (1.0f - bonusPercentage);
    this->speedBuff = (1.0f - bonusPercentage);
}

void Tower::resetSpeedBuff() {
    this->speedBuff = 1;
}

void Tower::addArmor() {
    if (this->armorPierceValue < 30)
        this->armorPierceValue = this->armorPierceValue + 5;
}

bool Tower::getIsPlaced () {
    return (this->isPlaced);
}

void Tower::setIsPlaced(bool newPlaced) {
    this->isPlaced = newPlaced;
}
