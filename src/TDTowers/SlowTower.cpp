#include "SlowTower.hpp"


SlowTower::SlowTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window): Tower(gameInstance, 2, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "SlowTower",
                                                                                                                                                                      {8, 12, 16}, {400, 550, 700}, 8, 1.5, 4, false){
}
