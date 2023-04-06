#include "Tower.hpp"

class AttackSpeedTower : Tower{

    private:
        std::vector<float> attackSpeedBoost;
        std::vector<Tower *> towersList;
        std::vector<Tower *> towersInRange;
public :
        AttackSpeedTower(Game gameInstance, std::vector<Tower *> towersList);
        AttackSpeedTower(Game gameInstance, int xPos, int yPos, std::vector<Tower *> towersList);
        void boostTower(Tower &tower);
        void resetBoostTower(Tower &tower);
        //! override
        void activate(std::vector<TDUnit *> enemyList);
        bool isInRange(Tower tower);
        void upgrade();

};