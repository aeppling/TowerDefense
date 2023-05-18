#include "SniperTower.hpp"

SniperTower::SniperTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, SFTowerSoundLoader &soundLoader): Tower(gameInstance, 3, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "SniperTower",
                                                                                                                                                                              {50, 100, 150}, {500, 700, 900}, {17, 25, 30}, {4.5, 4, 3.7}, 9, false, soundLoader){
}