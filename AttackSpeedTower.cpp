#include "AttackSpeedTower.hpp"

AttackSpeedTower::AttackSpeedTower(Game gameInstance, std::vector<Tower *> towersList):Tower(gameInstance){
    this->damage = {0,0,0};
    this->size = {2,2};
    this->cost = {600, 1000, 1500};
    this->range = 4;
    this->timeBetweenAttack = 0;
    this->attackSpeedBoost = {1.5,2,3};
    this->towersList = towersList;
}
AttackSpeedTower::AttackSpeedTower(Game gameInstance, int xPos, int yPos, std::vector<Tower *> towersInRange):Tower(gameInstance, xPos, yPos){
    this->damage = {0,0,0};
    this->size = {2,2};
    this->cost = {600, 1000, 1500};
    this->range = 4;
    this->timeBetweenAttack = 0;
    this->attackSpeedBoost = {1.5};
    this->towersInRange = towersInRange;
}

bool AttackSpeedTower::isInRange(Tower tower){
    //* return true if tower is in the range of the tower
    if (tower.getPosition().x <= this->coord.x + this->range + this->size.x && tower.getPosition().x >= this->coord.x - this->range && tower.getPosition().y <= this->coord.y + this->range + this->size.y && tower.getPosition().y >= this->coord.y - this->range){
        return true;
    } else{
        return false;
    }
}

void AttackSpeedTower::boostTower(Tower &tower){
    //* Boost the tower speed  attack boost
    tower.setTimeBetweenAttack(tower.getTimeBetweenAttack()/this->attackSpeedBoost[this->level]);
    tower.setSpeedBoosted(true);
}
void AttackSpeedTower::resetBoostTower(Tower &tower){
    //* reset the tower speed attack boost
    tower.setTimeBetweenAttack(tower.getTimeBetweenAttack()*this->attackSpeedBoost[this->level]);
    tower.setSpeedBoosted(false);
}


void AttackSpeedTower::activate(std::vector<TDUnit *> enemiesList){
    //* run while tower is activated
    std::cout << "Tower activated" << std::endl;
    this->activated = true;
    while(this->activated){
        for(int i = 0; i<=towersList.size(); i++){
            
            if(this->isInRange(towersList[i]) && towersList[i].!isSpeedBoosted()){
                this->boostTower(towersList[i]);
            }else if(this->!isInRange(towersList[i]) && towersList[i].isSpeedBoosted()) {
                this->resetBoostTower(towersList[i]);
            }
        }
    }
}

void AttackSpeedTower::upgrade(){
    if(this->level += 1 < this->cost.size() ){
        this->level++;
        std::cout << " Tower upgraded from level " << this->level-1 << " to " << this->level << std::endl;
    }else{
        std::cout << "The tower level is already maxed" << std::endl;
    }
}


