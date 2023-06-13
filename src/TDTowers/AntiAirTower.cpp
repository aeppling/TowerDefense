#include <algorithm>
#include "AntiAirTower.hpp"

AntiAirTower::AntiAirTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlTowerLoader, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, SFTowerSoundLoader &soundLoader): Tower(gameInstance, 3, cellSize, sfmlTowerLoader, sfmlMissileLoader, window, "AntiAirTower",
                                                                                                      {100, 140, 180}, {400, 550, 700}, {12, 13, 15}, {4, 3.8, 3.2}, 3.5, true, soundLoader){
}