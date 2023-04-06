#include "Tower.hpp"

class SlowTower : Tower{

    private:
        std::vector<int> slowValue;
    public:
        SlowTower(Game gameInstance);
        SlowTower(Game gameInstance, int xPos, int yPos);
        void slowTarget(Enemy target);
        void resetSlowTarget(Enemy target);
        //! Override
        void removeFromEnemiesInRangeList(Enemy enemy);
        void addToEnemiesInRangeList(Enemy enemy);
        void upgrade();

};