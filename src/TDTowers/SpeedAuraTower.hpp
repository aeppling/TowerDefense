//
// Created by adrie on 09/05/2023.
//

#ifndef UNTITLED1_SPEEDAURATOWER_HPP
#define UNTITLED1_SPEEDAURATOWER_HPP

#include "Tower.hpp"

class SpeedAuraTower : public Tower {
private:
    std::vector<Tower*> *_towerList;
    std::vector<Tower *> _towerInRange;
public:
    SpeedAuraTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlLoaderTower, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, SFTowerSoundLoader &soundLoader);
    void isInRange() override;
    void activate(std::vector<Tower*> *towerList);
    void deactivate() override;
    void live(std::vector<Tower*> *towerList);
    void run(std::vector<Tower*> *towerList);
    void setSpeedTowerBuff();
    void addToTowerInRangeList(Tower *tower);
    void removeFromTowerInRangeList(Tower *tower);
    void resetAllBuff();
};

#endif //UNTITLED1_SPEEDAURATOWER_HPP
