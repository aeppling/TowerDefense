#include <algorithm>
#include "AntiAirTower.hpp"

AntiAirTower::AntiAirTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window): Tower(gameInstance, 3, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "AntiAirTower",
                                                                                                      {80, 100, 140}, {400, 550, 700}, 12, 4, 3.5, true){
}

/*void AntiAirTower::isInRange(std::vector<TDUnit *> enemiesList){

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
}*/