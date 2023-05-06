//
// Created by adrie on 11/04/2023.
//

#include "BasicTower.hpp"

BasicTower::BasicTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, SFTowerSoundLoader &soundLoader): Tower(gameInstance, 2, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "BasicTower",
                                                                                                  {20, 30, 40}, {200, 350, 500}, 7, 0.7, 5, false, soundLoader){
}