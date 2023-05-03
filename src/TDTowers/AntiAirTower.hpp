#include "Tower.hpp"

class AntiAirTower : public Tower{

    public :
        AntiAirTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlLoaderTower, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window);
        AntiAirTower(Game gameInstance, int xPos, int yPos);
        //! override

};