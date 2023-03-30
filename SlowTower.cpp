#include "SlowTower.hpp"


SlowTower::SlowTower(Game gameInstance):Tower(gameInstance){
    this->slowValue = {10,20,30};
    this->damage = {0,0,0};
    this->size = {2,2};
    this->cost = {400,700,900};
    this->range = 4;
    this->timeBetweenAttack = 0;
}
SlowTower::SlowTower(Game gameInstance, int xPos, int yPos):Tower(gameInstance, xPos, yPos){
    this->slowValue = {10,20,30};
    this->damage = {0,0,0};
    this->size = {2,2};
    this->cost = {400,700,900};
    this->range = 4;
    this->timeBetweenAttack = 0;
}

void SlowTower::slowTarget(Enemy target){
    //* decrease the target speed
    target.setSpeed(target.GetSpeed()-this->slowValue[this->level]);
}

void SlowTower::resetSlowTarget(Enemy target){
    //* reset the target speed
    target.setSpeed(target.GetSpeed()+this->slowValue[this->level]);
}

void SlowTower::addToEnemiesInRangeList(Enemy enemy){
    //* slow the target and add him to in range list
    this->slowTarget(enemy);
    Tower::AddToEnemiesInRangeList(enemy);   
}

void SlowTower::removeFromEnemiesInRangeList(Enemy enemy){
    //* reset the target speed and add him to in range list
    this->resetSlowTarget(enemy);
    Tower::RemoveFromEnemiesInRangeList(enemy);
}

void SlowTower::upgrade(){
    if(this->level += 1 < this->cost.size() ){
        this->level++;
        std::cout << " Tower upgraded from level " << this->level-1 " to " << this->level << std::endl;
    }else{
        std::cout << "The tower level is already maxed" << std::endl;
    }
}
