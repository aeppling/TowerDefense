#include "Tower.hpp"

class AttackSpeedTower : public Tower{

public :
        AttackSpeedTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlLoaderTower, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, SFTowerSoundLoader &soundLoader);
        ~AttackSpeedTower() {};

};