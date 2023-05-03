#include "Tower.hpp"

class AttackSpeedTower : public Tower{

     /*   std::vector<float> attackSpeedBoost;
        std::vector<Tower *> towersList;
        std::vector<Tower *> towersInRange;*/
public :
        AttackSpeedTower(Game *gameInstance, int cellSize, SFMLTowerLoader &sfmlLoaderTower, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window);
        ~AttackSpeedTower() {};
  //  void boostTower(Tower &tower);
    //    void resetBoostTower(Tower &tower);
};