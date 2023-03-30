#include <algorithm>
#include "AntiAirTower.hpp"

AntiAirTower::AntiAirTower(Game gameInstance):Tower(gameInstance){
    
    this->damage = {150, 250, 400};
    this->cost = {350, 500, 700};
    
    this->size = {2,2};
    this->range = 10;
    this->timeBetweenAttack = 5;
}

AntiAirTower::AntiAirTower(Game gameInstance, int xPos, int yPos):Tower( gameInstance, xPos, yPos){
    this->damage = {150, 250, 400};
    this->cost = {350, 500, 700};
    this->size = {2,2};
    
    this->range = 10;
    this->timeBetweenAttack = 5;
}

void AntiAirTower::isInRange(std::vector<TDUnit *> enemiesList){

    //* if enemy is in the tower's range and aerian add him to the vector, if he isnt, remove him
    for(TDUnit *enemy : enemiesList){
        if(enemy->isFlying()){
            if(enemy->getPosX() <= this->coord.x + this->range + this->size.x && enemy->getPosX() >= this->coord.x - this->range && enemy->getPosY() <= this->coord.y + this->range + this->size.y && enemy->getPosY() >= this->coord.y - this->range){
                if( std::find(this->enemiesInRange.begin(),this->enemiesInRange.end(), enemy ) != this->enemiesInRange.end()){
                    this->addToEnemiesInRangeList(enemy);
                }
            }else{
                if( std::find(this->enemiesInRange.begin(),this->enemiesInRange.end(), enemy ) != this->enemiesInRange.end()){
                    this->removeFromEnemiesInRangeList(enemy);
                }
            }
        }
    }
}