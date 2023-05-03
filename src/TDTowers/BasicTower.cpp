//
// Created by adrie on 11/04/2023.
//

#include "BasicTower.hpp"

BasicTower::BasicTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window): Tower(gameInstance, 2, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "BasicTower",
                                                                                                  {20, 2, 4}, {100, 200, 400}, 7, 0.7, 5, false){
}