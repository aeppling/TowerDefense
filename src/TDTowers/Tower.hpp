#ifndef TOWER_HPP_
#define TOWER_HPP_

#include "../TDUnits/TDUnit.hpp"
#include "../TDGame/Game.hpp"
#include "../TDGame/usefullStruct.hpp"
#include "../TDGame/Buildable.hpp"
#include "../TDGraphics/SFMLTowerLoader.hpp"
#include "../TDGraphics/SFMLMissileLoader.hpp"
#include "../TDTowers/MissileLauncher.hpp"
#include "../TDSounds/SFTowerSoundLoader.hpp"

#include <vector>
#include <thread>
#include <algorithm> 

class Game;

class Tower : public Buildable {
    //* Basic parent tower Class
    protected:
        //Game gameInstance;
        Point coord;
        std::vector<Tower *> towersList;
        std::vector<TDUnit *> enemiesInRange;
        std::string towerName;
         std::shared_ptr<std::vector<TDUnit*>> enemiesList;
        std::vector<int> damage;
        std::vector<int> cost;
        std::vector<float> slowValue;
        int level;
        bool speedBoosted;
        float speedBuff;
        bool activated;
        std::vector<float> range;
        std::vector<float> timeBetweenAttack;
        bool aerial;
        float missileSpeed;
        std::thread _towerThread;
        Game        *gameInstance;
        std::chrono::steady_clock::time_point _timeOfLastShot; // SET WITH time(NULL) and reset at every move
        sf::Sprite towerSprite;
        MissileLauncher *missileLauncher;
        sf::RenderWindow &window;
        sf::Sound       _shotSound;
        sf::Sound       _killSound;
public:
        Tower(Game *gameInstance, int size, int cellSize, SFMLTowerLoader &sfmlLoaderTower, SFMLMissileLoader &sfmlMissileLoader, sf::RenderWindow &window, std::string towerName,
              std::vector<int> damage, std::vector<int> cost, std::vector<float> range, std::vector<float> timeBetweenAttack, float missileSpeed, bool isAerial, SFTowerSoundLoader &soundLoader);
        ~Tower() override { this->_towerThread.join(); };
        std::string getTowerName();
        sf::Sprite getTowerSprite() { return (this->towerSprite); };
        sf::Sprite *getTowerSpritePtr() { return (&this->towerSprite); };
        void setCurrentWave(std::shared_ptr<std::vector<TDUnit*>> enemiesList);
        void removeFromEnemiesInRangeList(TDUnit *enemy) override;
        void addToEnemiesInRangeList(TDUnit *enemy) override;
        void activate(std::shared_ptr<std::vector<TDUnit*>> enemiesList) override;
        void deactivate() override;
        void rotate(TDUnit *target);
        void animateFiring();
        void fire(TDUnit *target) override;
        void isInRange() override;
        void upgrade(SFMLTowerLoader &sfmlTowerLoader) override;
        void setTimeBetweenAttack(float time) override;
        float getTimeBetweenAttack() override;
        int getCost() override;
        int getUpgradeCost();
        int getLevel() override;
        bool isSpeedBoosted() override;
        void setSpeedBoosted(bool newSpeedBoosted) override;
        void setPosition(int posX, int posY, int cellSize) override;
        int getDamage();
        int getUpgradeDamage();
        Point getPosition() override;
        bool isActivated();
        int getRange();
        void join();
        void run(std::shared_ptr<std::vector<TDUnit*>> enemiesList) override;
        void live(std::shared_ptr<std::vector<TDUnit*>> levelEnemyList) override;
        bool isMaxed() override;
        sf::Sprite getMissileSprite(int index);
        sf::Sprite getExplosionSprite(int index);
        int getTotalMissiles();
        void slowTarget(TDUnit *target);
        void resetSlowTarget(TDUnit *target);
        void setSpeedBuffValue(int value);
        float getSpeedBuff() { return (this->speedBuff);};
        void resetSpeedBuff();
};

#endif