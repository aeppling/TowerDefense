#include "Tower.hpp"

class AttackSpeedTower : public Tower{

    private:
        std::vector<float> attackSpeedBoost;
        std::vector<Tower *> towersList;
        std::vector<Tower *> towersInRange;
public :
        AttackSpeedTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlLoaderTower);
        ~AttackSpeedTower() {};
        void boostTower(Tower &tower);
        void resetBoostTower(Tower &tower);
        //! override
       // void activate(std::vector<TDUnit *> enemyList);
        void upgrade();

};