#include "Tower.hpp"

class SplashTower : public Tower {
    private:
        int area;
    public :
        SplashTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlLoaderTower, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window);
        ~SplashTower() {};
        //! override
       // void fire(TDUnit *target);
};