#include "Tower.hpp"

class AntiAirTower : Tower{

    public :
        AntiAirTower(Game gameInstance);
        AntiAirTower(Game gameInstance, int xPos, int yPos);
        //! override
        void isInRange(std::vector<TDUnit *> enemiesList);

};