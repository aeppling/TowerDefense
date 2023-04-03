#include <unistd.h>
#include "Tower.hpp"

Tower::Tower(Game *gameInstance, int size) : Buildable(size, "Tower")  {
    this->gameInstance = gameInstance;
    this->level = 0;
    this->coord = {0, 0};
    this->damage = {20, 40, 60};
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


void Tower::live(std::vector<TDUnit*> &levelEnemyList) {
    this->activate(levelEnemyList);
}
void Tower::run(std::vector<TDUnit *> &enemiesList){
    //* run the tower threadst
    std::cout << "Tower running..." << std::endl;
    this->gameInstance->getCurrentWaveNumber();
    this->_towerThread = std::thread(&Tower::live, this, std::ref(enemiesList));
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
    std::cout << "Number of ennemies : " << enemiesList.size() << std::endl;
    this->enemiesInRange.push_back(enemiesList[0]);
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
    while(this->activated) { // EXITING TO QUICKLY ?
        std::cout << "Check range" << std::endl;
        isInRange(this->enemiesList);
        if(enemiesInRange.size() > 0 && this->damage[this->level] > 0){
            //* Fire on ennemies in tower range
            std::cout << "Enemy shot by tower." << std::endl;
            this->fire(this->enemiesInRange.at(0));
            //* wait time between fire
            std::this_thread::sleep_for(std::chrono::milliseconds(1000) * this->timeBetweenAttack);
//            usleep(this->timeBetweenAttack * 1000);
//            sleep(this->timeBetweenAttack*1000);
        }
    }
    std::cout << "Leaving tower loop" << std::endl;
}
void Tower::deactivate(){
    //* Deactivate the tower
    std::cout << "Tower Deactivated" << std::endl;
    this->activated = false;
    this->enemiesList.clear();
    this->enemiesInRange.clear();

  // this->enemiesList = new std::vector<TDUnit *>();
  // this->enemiesInRange =  new std::vector<TDUnit *>();
}

void Tower::fire(TDUnit *target){
    //* remove target health
    target->setHealth(target->getHealth()-this->damage[this->level]);
    if(target->getHealth() <= 0){
        std::cout << "enemy killed" << std::endl;
      //  this->gameInstance.addCoins(target->getValue());
        removeFromEnemiesInRangeList(target);
        std::cout << "Here 1" << std::endl;
        delete target;
        std::cout << "Here 2" << std::endl;
        this->enemiesList.erase(std::remove(this->enemiesList.begin(), this->enemiesList.end(), target), this->enemiesList.end());
        std::cout << "Here 3" << std::endl;
    }
    std::cout << "Here 3" << std::endl;
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

void Tower::setPosition(int newXPos, int newYPos){
    this->coord = {newXPos,newYPos};
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


