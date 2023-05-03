#include <unistd.h>
#include <mutex>
#include <math.h>
#include "Tower.hpp"
#include "../TDGraphics/SFMLMissileLoader.hpp"
#include "../TDGame/usefullStruct.hpp"

std::mutex mtx;

Tower::Tower(Game *gameInstance, int size, int cellSize, SFMLTowerLoader &sfmlLoaderTower, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, std::string towerName,
             std::vector<int> damage, std::vector<int> cost, float range, float timeBetweenAttack, float missileSpeed, bool isAerial) : window(window), Buildable(size, "Tower") {
    this->towerName = towerName;
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
    else {
        std::cout << "Tower name not found ... Cannot add to shop." << std::endl;
        return ;
    }
    this->missileSpeed = missileSpeed;
    this->missileLauncher = new MissileLauncher(sfmlMissileLoader, cellSize, this->towerName);
    float scaleFactor = static_cast<float>(cellSize) / static_cast<float>(this->towerSprite.getTexture()->getSize().y);
    sf::IntRect textureRect(0, 0, this->towerSprite.getTexture()->getSize().y, this->towerSprite.getTexture()->getSize().y);
    if ((this->towerName == "SlowTower") || (this->towerName == "SplashTower"))
        this->towerSprite.setScale(scaleFactor * 2.5, scaleFactor * 2.5);
    else if (this->towerName == "SniperTower")
        this->towerSprite.setScale(scaleFactor * 3, scaleFactor * 3);
    else
        this->towerSprite.setScale(scaleFactor * 3.5, scaleFactor * 3.5);
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
    //   this->enemiesInRange.push_back(enemiesList[0]);
    //* if enemy is in the tower's range add him to the vector, if he isnt, remove him

    for (TDUnit *enemy: *(this->enemiesList)) {
        mtx.lock();
        if ((enemy->getPosX() <= this->coord.x + this->range + this->getSize() &&
            enemy->getPosX() >= this->coord.x - this->range &&
            enemy->getPosY() <= this->coord.y + this->range + this->getSize() &&
            enemy->getPosY() >= this->coord.y - this->range) && !(((enemy->isFlying() == true) && (this->aerial == false)) || ((enemy->isFlying() == false) && (this->aerial == true)))){
            if (std::find(this->enemiesInRange.begin(), this->enemiesInRange.end(), enemy) ==
                this->enemiesInRange.end()) {
                addToEnemiesInRangeList(enemy);
            }
        } else {
            if (std::find(this->enemiesInRange.begin(), this->enemiesInRange.end(), enemy) !=
                this->enemiesInRange.end()) {
                removeFromEnemiesInRangeList(enemy);
            }

        }
        mtx.unlock();
    }
}

void Tower::activate(std::shared_ptr<std::vector<TDUnit*>> enemiesList){
    //* run while tower is activated 
    this->enemiesList = enemiesList;
    this->activated = true;
        while (this->activated) { // EXITING TO QUICKLY ?
            if (this->activated == false)
                break;
            isInRange();
            if (enemiesInRange.size() > 0 && this->damage[this->level] > 0) {
                //* Fire on ennemies in tower range
                std::chrono::steady_clock::time_point testTime = std::chrono::steady_clock::now();
                int res = std::chrono::duration_cast<std::chrono::milliseconds>(
                        testTime - this->_timeOfLastShot).count();
                if (!this->enemiesInRange.empty())
                    this->rotate(this->enemiesInRange.at(0));
                if (res >= this->timeBetweenAttack * 1000) {
                    this->fire(this->enemiesInRange.at(0));
                    this->_timeOfLastShot = std::chrono::steady_clock::now();
                }
                //* wait time between fire
                // CHANGE TO TIME SINCE LAST SHOT < TIME FOR SHOOT == SHOOT
                // std::this_thread::sleep_for(std::chrono::milliseconds(1000) * this->timeBetweenAttack);
            }
        }
}

void Tower::deactivate(){
    //* Deactivate the tower
  //  if (this->_towerThread.joinable())
    //    this->_towerThread.join();
    this->activated = false;
    this->enemiesList->clear();
    this->enemiesInRange.clear();
    // this->enemiesList = new std::vector<TDUnit *>();
  // this->enemiesInRange =  new std::vector<TDUnit *>();
}

bool Tower::isActivated() {
    return (this->activated);
}
void Tower::join() {
    this->_towerThread.join();
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
    //* remove target health
   // target->setHealth(target->getHealth()-this->damage[this->level]);
    // Get the position of the tower and the target
    if (target->_isKilled == true) {
        removeFromEnemiesInRangeList(target);
        return ;
    }
    this->rotate(target);
    try  {
        mtx.lock();
        std::thread animationThread(&Tower::animateFiring, this);
        animationThread.detach();
        this->missileLauncher->shoot(this->towerSprite.getPosition().x, this->towerSprite.getPosition().y, target, this->missileSpeed);
        target->getShot(this->damage[this->level], 200);
        if (target->getHealth() <= 0) {
            //  this->gameInstance.addCoins(target->getValue());
            removeFromEnemiesInRangeList(target);
            this->enemiesList->erase(std::remove(this->enemiesList->begin(), this->enemiesList->end(), target), this->enemiesList->end());
            target->getKill();

        }
    } catch (const std::system_error& ex) {
        std::cerr << "Caught std::system_error exception: " << ex.what() << std::endl;
        // Additional error handling or recovery logic
    }
    this->missileLauncher->endFinishedThreads();
    mtx.unlock();
}

void Tower::upgrade(){
    //* upgrade tower level and stats
    if(!this->isMaxed()){
        this->level++;
        std::cout << " Tower upgraded from level " << this->level-1 << " to " << this->level << std::endl;
    }else{
        std::cout << "The tower level is already maxed" << std::endl;
    } 
}

//* getters | setters

int Tower::getDamage(){
    return (this->damage[this->level]);
}
float Tower::getTimeBetweenAttack(){
    return (this->timeBetweenAttack);
}
void Tower::setTimeBetweenAttack(float time){
    this->timeBetweenAttack = time;
}

bool Tower::isSpeedBoosted(){
    return (this->speedBoosted);
}

void Tower::setSpeedBoosted(bool newSpeedBoosted){
    this->speedBoosted = speedBoosted;
}

int Tower::getCost(){
    return (this->cost[this->level]);
}
int Tower::getLevel(){
    return (this->level);
}

int Tower::getRange() {
    return (this->range);
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

int Tower::getTotalMissiles() {
    return (this->missileLauncher->getTotalMissiles());
}

bool Tower::isMaxed(){
    if (this->level += 1 < this->cost.size()) {
        return true;
    } else {
        return false;
    }

}


