#include "SniperTower.hpp"

SniperTower::SniperTower(Game gameInstance):Tower(gameInstance, xPos, yPos){
    this->damage = {100, 300, 500};
    this->size = {2,2};
    this->cost = {250, 400, 550};
    this->range = 10;
    this->timeBetweenAttack = 5;
}
SniperTower::SniperTower(Game gameInstance, int xPos, int yPos):Tower(gameInstance, xPos, yPos){
    this->damage = {100, 300, 500};
    this->size = {2,2};
    this->cost = {250, 400, 550};
    this->range = 10;
    this->timeBetweenAttack = 5;
}