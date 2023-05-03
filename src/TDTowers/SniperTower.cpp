#include "SniperTower.hpp"

SniperTower::SniperTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window): Tower(gameInstance, 2, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "SniperTower",
                                                                                                                                                                              {35, 45, 60}, {500, 700, 850}, 25, 4.5, 7.5, false){
}