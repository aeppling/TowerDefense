#include <unistd.h>
#include "Tower.hpp"

Tower::Tower(Game *gameInstance, int size) : Buildable(size, "Tower")  {
    this->gameInstance = gameInstance;
    this->level = 0;
    this->coord = {0, 0};
    this->damage = {20, 40, 60 };
    this->cost = {100, 200, 400};
  //  this->enemiesInRange =  new std::vector<TDUnit *>();
    this->range = 5;
    this->timeBetweenAttack = 1.5;
    this->activated = true;
    this->aerial = false;
   // this->enemiesList = new std::vector<TDUnit *>();
    this->speedBoosted = false;
}

Tower::Tower(Game *gameInstance, int xPos, int yPos, int size) : Buildable(size, "Tower") {
    this->gameInstance = gameInstance;
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


void Tower::live(std::vector<std::vector<TDUnit*>> &levelEnemyList, int *waveNumber) {
   // this->activate(levelEnemyList.at(waveNumber));
}
void Tower::run(std::vector<TDUnit *> &enemiesList){
    //* run the tower threadst
    std::cout << "Tower running..." << std::endl;
    this->gameInstance->getCurrentWaveNumber();
  //  this->_towerThread = std::thread(live, enemiesList, this->gameInstance->ge);
}

void Tower::removeFromEnemiesInRangeList(TDUnit *enemy){
    //* Remove enemy from enemies in range vector
    this->enemiesInRange.erase(std::remove(enemiesInRange.begin(), enemiesInRange.end(), enemy), enemiesInRange.end());
}

void Tower::addToEnemiesInRangeList(TDUnit *enemy){
    //* Add enemy to enemies in range vector
    this->enemiesInRange.push_back(enemy);
}

void Tower::isInRange(std::vector<TDUnit *> &enemiesList){
    //* if enemy is in the tower's range add him to the vector, if he isnt, remove him
    //for(TDUnit *enemy : enemiesList){
/*        if(enemy->getPosX() <= this->coord.x + this->range + this->size.x && enemy->getPosX() >= this->coord.x - this->range && enemy->getPosY() <= this->coord.y + this->range + this->size.y && enemy->getPosY() >= this->coord.y - this->range){
            if(std::find(this->enemiesInRange.begin(),this->enemiesInRange.end(), enemy ) != this->enemiesInRange.end()){
                addToEnemiesInRangeList(enemy);
            }
        }else{
            if(std::find(this->enemiesInRange.begin(),this->enemiesInRange.end(), enemy ) != this->enemiesInRange.end()){
                removeFromEnemiesInRangeList(enemy);
            }*/
}

void Tower::activate(std::vector<TDUnit *> &enemiesList){
    //* run while tower is activated 
    this->enemiesList = enemiesList;
    std::cout << "Tower activated" << std::endl;
    this->activated = true;
    while(this->activated){
        isInRange(this->enemiesList);
        if(enemiesInRange.size() > 0 && this->damage[this->level] > 0){
            //* Fire on ennemies in tower range
            this->fire(this->enemiesInRange.at(0));
            //* wait time between fire
            sleep(this->timeBetweenAttack*1000);
        }
    }
}
void Tower::deactivate(){
    //* Deactivate the tower
    std::cout << "Tower Deactivated" << std::endl;
    //this->activated = false;
    //this->enemiesList.clear();
    //this->enemiesInRange.clear();

  //  this->enemiesList = new std::vector<TDUnit *>();
   // this->enemiesInRange =  new std::vector<TDUnit *>();
}

void Tower::fire(TDUnit *target){
    //* remove target health
    target->setHealth(target->getHealth()-this->damage[this->level]);
    if(target->getHealth() <= 0){
        std::cout << "enemy killed" << std::endl;
      //  this->gameInstance.addCoins(target->getValue());
        removeFromEnemiesInRangeList(target);
        this->enemiesList.erase(std::remove(this->enemiesList.begin(), this->enemiesList.end(), target), this->enemiesList.end());       
    }   
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
    return this->timeBetweenAttack;
}
void Tower::setTimeBetweenAttack(float time){
    this->timeBetweenAttack = time;
}

bool Tower::isSpeedBoosted(){
    return this->speedBoosted;
}

void Tower::setSpeedBoosted(bool newSpeedBoosted){
    this->speedBoosted = speedBoosted;
}

int Tower::getCost(int level){
    return this->cost[level];
}
int Tower::getLevel(){
    return this->level;
}

void Tower::setPosition(int newXPos, int newYPos){
    this->coord = {newXPos,newYPos};
}

Point Tower::getPosition(){
    return this->coord;
}

bool Tower::isMaxed(){
    if(this->level += 1 < this->cost.size()){
        return true;
    }else{
        return false;
    }

}


