#include "Tower.hpp"

class SniperTower : public Tower {

    private:
        
        
    public :
        SniperTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlLoaderTower, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window);
        ~SniperTower() {};
};