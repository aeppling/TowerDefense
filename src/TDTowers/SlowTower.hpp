#ifndef SLOWTOWER_HPP_
#define SLOWTOWER_HPP_

#include "Tower.hpp"
#include "../TDUnits/TDUnit.hpp"

class SlowTower : public Tower{

    private:
        std::vector<int> slowValue;
    public:
        SlowTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlLoaderTower, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window);
        //! Override
        void removeFromEnemiesInRangeList(TDUnit *enemy);
        void addToEnemiesInRangeList(TDUnit *enemy);
};

#endif /* SLOWTOWER_HPP_ */