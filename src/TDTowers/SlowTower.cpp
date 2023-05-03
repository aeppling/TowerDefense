#include "SlowTower.hpp"


SlowTower::SlowTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window): Tower(gameInstance, 2, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "SlowTower",
                                                                                                                                                                      {8, 12, 16}, {400, 550, 700}, 8, 1.5, 4, false){
}




void SlowTower::addToEnemiesInRangeList(TDUnit *enemy){
    // slow the target and add him to in range list
    this->slowTarget(enemy);
    Tower::addToEnemiesInRangeList(enemy);
}

void SlowTower::removeFromEnemiesInRangeList(TDUnit *enemy){
    // reset the target speed and add him to in range list
    this->resetSlowTarget(enemy);
    Tower::removeFromEnemiesInRangeList(enemy);
}
