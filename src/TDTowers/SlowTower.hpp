#ifndef SLOWTOWER_HPP_
#define SLOWTOWER_HPP_

#include "Tower.hpp"
#include "../TDUnits/TDUnit.hpp"

class SlowTower : public Tower{
 public:
        SlowTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlLoaderTower, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, SFTowerSoundLoader &soundLoader);
        //! Override
        void fire(TDUnit *target) override;
};

#endif /* SLOWTOWER_HPP_ */