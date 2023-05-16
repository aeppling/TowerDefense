//
// Created by adrie on 11/04/2023.
//

#include "BasicTower.hpp"

BasicTower::BasicTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, SFTowerSoundLoader &soundLoader): Tower(gameInstance, 3, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "BasicTower",
                                                                                                  {20, 40, 60}, {200, 350, 500}, {7, 8, 10}, {1.5, 1.5, 1.5}, 5, false, soundLoader){
}