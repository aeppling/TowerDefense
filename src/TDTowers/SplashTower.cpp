#include "SplashTower.hpp"

SplashTower::SplashTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, SFTowerSoundLoader &soundLoader): Tower(gameInstance, 3, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "SplashTower",
                                                                                                                                                                              {13, 20, 30}, {650, 800, 1000}, 10, 2.5, 0, false, soundLoader){
}

/*void SplashTower::fire(TDUnit *target){
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
}*/