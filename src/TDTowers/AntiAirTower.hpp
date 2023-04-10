#include "Tower.hpp"

class AntiAirTower : public Tower{

    public :
        AntiAirTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlLoaderTower);
        AntiAirTower(Game gameInstance, int xPos, int yPos);
        //! override
        void isInRange(std::vector<TDUnit *> enemiesList);

};