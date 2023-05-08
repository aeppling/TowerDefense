#include <mutex>
#include "SlowTower.hpp"

std::mutex slow_mtx;

SlowTower::SlowTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, SFTowerSoundLoader &soundLoader): Tower(gameInstance, 3, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "SlowTower",
                                                                                                                                                                      {8, 12, 16}, {400, 550, 700}, {8, 9, 10}, {1.5, 1.5, 1.5}, 4, false, soundLoader){
}

