#include "Tower.hpp"

class SplashTower : Tower{

    private:
        int area;
    public :
        SplashTower(Game gameInstance);
        SplashTower(Game gameInstance, int xPos, int yPos);
        //! override
        void fire(Enemy target);
};