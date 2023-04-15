#include "AttackSpeedTower.hpp"

AttackSpeedTower::AttackSpeedTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window): Tower(gameInstance, 2, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "AttackSpeedTower",
                                                                                                              {4, 8, 13}, {350, 500, 700}, 7, 0.2){
}

/*void AttackSpeedTower::boostTower(Tower &tower){
    //* Boost the tower speed  attack boost
    tower.setTimeBetweenAttack(tower.getTimeBetweenAttack()/this->attackSpeedBoost[this->level]);
    tower.setSpeedBoosted(true);
}*/
/*void AttackSpeedTower::resetBoostTower(Tower &tower){
     reset the tower speed attack boost
    tower.setTimeBetweenAttack(tower.getTimeBetweenAttack()*this->attackSpeedBoost[this->level]);
    tower.setSpeedBoosted(false);
}*/


/*void AttackSpeedTower::activate(std::vector<TDUnit *> enemiesList){
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
}*/

/*void AttackSpeedTower::upgrade(){
    if(this->level += 1 < this->cost.size() ){
        this->level++;
        std::cout << " Tower upgraded from level " << this->level-1 << " to " << this->level << std::endl;
    }else{
        std::cout << "The tower level is already maxed" << std::endl;
    }
}*/


