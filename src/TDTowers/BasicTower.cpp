//
// Created by adrie on 11/04/2023.
//

#include "BasicTower.hpp"

BasicTower::BasicTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, SFTowerSoundLoader &soundLoader): Tower(gameInstance, 3, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "BasicTower",
                                                                                                  {20, 30, 40}, {200, 350, 500}, {7, 8, 9}, 1.5, 5, false, soundLoader){
}