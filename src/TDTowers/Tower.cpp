#include <unistd.h>
#include <mutex>
#include "Tower.hpp"

std::mutex mtx;

Tower::Tower(Game *gameInstance, int size, std::shared_ptr<std::vector<TDUnit*>> enemiesList, int cellSize, SFMLLoader &sfmlLoaderTower) : enemiesList(enemiesList), Buildable(size, "Tower")  {
    this->towerName = "BasicTower";
    if (this->towerName == "BasicTower") {
        this->towerSprite.setTexture(*sfmlLoaderTower.getTowerBasic());
        float scaleFactor = static_cast<float>(cellSize) / static_cast<float>(this->towerSprite.getTexture()->getSize().x);
        sf::IntRect textureRect(0, 0, this->towerSprite.getTexture()->getSize().x, this->towerSprite.getTexture()->getSize().y);
        this->towerSprite.setScale(scaleFactor * 2, scaleFactor * 2);
        this->towerSprite.setTextureRect(textureRect);
    }
    this->_timeOfLastShot = std::chrono::steady_clock::now();
    this->gameInstance = gameInstance;
    this->level = 0;
    this->coord = {0, 0};
    this->damage = {20, 2, 4};
    this->cost = {100, 200, 400};
  //  this->enemiesInRange =  new std::vector<TDUnit *>();
    this->range = 5;
    this->timeBetweenAttack = 1;
    this->activated = true;
    this->aerial = false;
   // this->enemiesList = new std::vector<TDUnit *>();
    this->speedBoosted = false;
}

Tower::Tower(Game *gameInstance, int xPos, int yPos, int size, std::shared_ptr<std::vector<TDUnit*>> enemiesList) : Buildable(size, "Tower") {
    this->_timeOfLastShot = std::chrono::steady_clock::now();
    this->gameInstance = gameInstance;
    this->towerName = "BasicTower";
    this->damage = {20, 40, 60 };
    this->cost = {100, 200, 400};
    this->level = 0;
   // this->enemiesInRange =  new std::vector<TDUnit *>();
    this->coord = {xPos, yPos};
    this->range = 5;
    this->timeBetweenAttack = 1.5;
    this->activated = true;
    this->aerial = false;
    //this->enemiesList = new std::vector<TDUnit *>();
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

/*bool Tower::isAlreadyInList() {

}*/

void Tower::isInRange() {
    //   this->enemiesInRange.push_back(enemiesList[0]);
    //* if enemy is in the tower's range add him to the vector, if he isnt, remove him
    for (TDUnit *enemy: *(this->enemiesList)) {
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
    }
}

void Tower::activate(std::shared_ptr<std::vector<TDUnit*>> enemiesList){
    //* run while tower is activated 
    this->enemiesList = enemiesList;
    std::cout << "Tower activated" << std::endl;
    this->activated = true;
    while(this->activated) { // EXITING TO QUICKLY ?
        if (this->activated == false)
            break;
        mtx.lock();
        isInRange();
        mtx.unlock();
        if(enemiesInRange.size() > 0 && this->damage[this->level] > 0){
            //* Fire on ennemies in tower range
            std::chrono::steady_clock::time_point testTime = std::chrono::steady_clock::now();
            int res = std::chrono::duration_cast<std::chrono::milliseconds>(testTime - this->_timeOfLastShot).count();
            if (res >= this->timeBetweenAttack * 1000) {
                this->fire(this->enemiesInRange.at(0));
                this->_timeOfLastShot = std::chrono::steady_clock::now();
            }
            //* wait time between fire
            // CHANGE TO TIME SINCE LAST SHOT < TIME FOR SHOOT == SHOOT
           // std::this_thread::sleep_for(std::chrono::milliseconds(1000) * this->timeBetweenAttack);
        }
    }
    std::cout << "Leaving tower loop" << std::endl;
}
void Tower::deactivate(){
    //* Deactivate the tower
  //  if (this->_towerThread.joinable())
    //    this->_towerThread.join();
    std::cout << "Tower Deactivated" << std::endl;
    this->activated = false;
    this->enemiesList->clear();
    this->enemiesInRange.clear();
    std::cout << "Tower Cleared" << std::endl;
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

void Tower::fire(TDUnit *target){
    //* remove target health
   // target->setHealth(target->getHealth()-this->damage[this->level]);
    mtx.lock();
    target->getShot(this->damage[this->level]);
    if (target->getHealth() <= 0) {
         // PROBLEM BECAUSE ALREADY DELETE BY HIMSELF ??
        //  this->gameInstance.addCoins(target->getValue());
        removeFromEnemiesInRangeList(target);
        this->enemiesList->erase(std::remove(this->enemiesList->begin(), this->enemiesList->end(), target), this->enemiesList->end());
        target->getKill();
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
    this->towerSprite.setOrigin(cellSize / 2, cellSize / 2);
    this->towerSprite.setPosition((newXPos * cellSize), (newYPos * cellSize));
}

Point Tower::getPosition(){
    return (this->coord);
}

bool Tower::isMaxed(){
    if (this->level += 1 < this->cost.size()) {
        return true;
    } else {
        return false;
    }

}


