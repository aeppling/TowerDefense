#include <unistd.h>
#include <mutex>
#include <math.h>
#include "Tower.hpp"
#include "../TDGraphics/SFMLMissileLoader.hpp"

std::mutex mtx;

Tower::Tower(Game *gameInstance, int size, int cellSize, SFMLTowerLoader &sfmlLoaderTower, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, std::string towerName,
             std::vector<int> damage, std::vector<int> cost, float range, float timeBetweenAttack) : window(window), Buildable(size, "Tower") {
    this->towerName = towerName;
    if (this->towerName == "BasicTower")
        this->towerSprite.setTexture(*sfmlLoaderTower.getBasic());
    else if (this->towerName == "AntiAirTower")
        this->towerSprite.setTexture(*sfmlLoaderTower.getBasic());
    else if (this->towerName == "AttackSpeedTower")
        this->towerSprite.setTexture(*sfmlLoaderTower.getSpeed());
    else if (this->towerName == "SlowTower")
        this->towerSprite.setTexture(*sfmlLoaderTower.getBasic());
    else if (this->towerName == "SniperTower")
        this->towerSprite.setTexture(*sfmlLoaderTower.getBasic());
    else if (this->towerName == "SplashTower")
        this->towerSprite.setTexture(*sfmlLoaderTower.getBasic());
    else {
        std::cout << "Tower name not found ... Cannot add to shop." << std::endl;
        return ;
    }
    this->missileLauncher = new MissileLauncher(sfmlMissileLoader, window, cellSize, towerName);
    std::cout << this->towerName << " added to shoplist." << std::endl;
    float scaleFactor = static_cast<float>(cellSize) / static_cast<float>(this->towerSprite.getTexture()->getSize().x);
    sf::IntRect textureRect(0, 0, this->towerSprite.getTexture()->getSize().x, this->towerSprite.getTexture()->getSize().y);
    this->towerSprite.setScale(scaleFactor * 2, scaleFactor * 2);
    this->towerSprite.setTextureRect(textureRect);
    sf::Vector2f newOrigin(this->towerSprite.getLocalBounds().width / 2.f, this->towerSprite.getLocalBounds().height / 2.f);
    this->towerSprite.setOrigin(newOrigin);
    this->_timeOfLastShot = std::chrono::steady_clock::now();
    this->gameInstance = gameInstance;
    this->level = 0;
    this->coord = {0, 0};
    this->damage = damage;
    this->cost = cost;
    this->range = range;
    this->timeBetweenAttack = timeBetweenAttack;
    this->activated = true;
    this->aerial = false;
    this->speedBoosted = false;
}

void Tower::live(std::shared_ptr<std::vector<TDUnit*>> levelEnemyList) {
    this->activate(levelEnemyList);
}

void Tower::run(std::shared_ptr<std::vector<TDUnit*>> enemiesList){
    //* run the tower threadst
    std::cout << "Tower running..." << std::endl;
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
        if (enemy->getPosX() <= this->coord.x + this->range + this->getSize() &&
            enemy->getPosX() >= this->coord.x - this->range &&
            enemy->getPosY() <= this->coord.y + this->range + this->getSize() &&
            enemy->getPosY() >= this->coord.y - this->range) {
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
                if (res >= this->timeBetweenAttack * 1000) {
                    this->fire(this->enemiesInRange.at(0));
                    this->_timeOfLastShot = std::chrono::steady_clock::now();
                }
                //* wait time between fire
                // CHANGE TO TIME SINCE LAST SHOT < TIME FOR SHOOT == SHOOT
                // std::this_thread::sleep_for(std::chrono::milliseconds(1000) * this->timeBetweenAttack);
            }
            sf::sleep(sf::milliseconds(15));
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
    std::cout << "Tower Joined" << std::endl;
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
        target->getShot(this->damage[this->level]);
        if (target->getHealth() <= 0) {
            //  this->gameInstance.addCoins(target->getValue());
            removeFromEnemiesInRangeList(target);
            this->enemiesList->erase(std::remove(this->enemiesList->begin(), this->enemiesList->end(), target), this->enemiesList->end());
            target->getKill();
        }
        this->missileLauncher->shoot(this->towerSprite.getPosition().x, this->towerSprite.getPosition().y, target);
    } catch (const std::system_error& ex) {
        std::cerr << "Caught std::system_error exception: " << ex.what() << std::endl;
        // Additional error handling or recovery logic
    }
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

int Tower::getCost(int level){
    return (this->cost[level]);
}
int Tower::getLevel(){
    return (this->level);
}

void Tower::setPosition(int newXPos, int newYPos, int cellSize){
    this->coord = {newXPos,newYPos};
    this->towerSprite.setPosition((newXPos * cellSize) + cellSize/2, ((newYPos * cellSize) + cellSize/2) - 5);
}

Point Tower::getPosition(){
    return (this->coord);
}

std::string Tower::getTowerName() { return (this->towerName); };

bool Tower::isMaxed(){
    if (this->level += 1 < this->cost.size()) {
        return true;
    } else {
        return false;
    }

}


