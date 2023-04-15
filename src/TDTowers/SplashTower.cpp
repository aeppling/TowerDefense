#include "SplashTower.hpp"

SplashTower::SplashTower(Game gameInstance):Tower(gameInstance){
    this->damage = {15, 40, 80};
    this->size = {2,3};
    this->cost = {500, 600, 700};
    this->range = 5;
    this->timeBetweenAttack = 1;
    this->area = 1;
}
SplashTower::SplashTower(Game gameInstance, int xPos, int yPos):Tower(gameInstance, xPos, yPos){
    this->damage = {15, 40, 80};
    this->size = {2,3};
    this->cost = {500, 600, 700};
    this->range = 5;
    this->timeBetweenAttack = 1;
    this->area = 1;
}

void SplashTower::fire(Enemy target){
    //* remove target health and all enemies around the target
    for each(Enemy hit in this->enemiesInRange){  
        if(hit.getXPos() <= target.getXPos() + this->area && hit.getXPos() >= target.getXPos() - this->area && hit.getYPos() <= target.getYPos() + this->area && hit.getYPos() >= target.getYPos() - this->area){
            hit.setHealth(hit.getHealth()-this->damage[this->level]);
            if(hit.GetHealth() <= 0){
                std::cout << "enemy killed" << std::endl;
                this->gameInstance.addCoins(hit.getValue());
                removeFromEnemiesInRangeList(hit);
                this->enemiesList.erase(std::remove(this->enemiesList.begin(), this->enemiesList.end(), target), this->enemiesList.end());
            
            }
        }
    }
}