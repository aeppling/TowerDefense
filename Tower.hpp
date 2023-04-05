#ifndef TOWER_HPP_
#define TOWER_HPP_

#include "TDUnit.hpp"
#include "Game.hpp"
#include "usefullStruct.hpp"
#include "Buildable.hpp"

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
        int level;
        bool speedBoosted;
        bool activated;
        float range;
        float timeBetweenAttack;
        bool aerial;
        std::thread _towerThread;
        Game        *gameInstance;
        std::chrono::steady_clock::time_point _timeOfLastShot; // SET WITH time(NULL) and reset at every move
        sf::Sprite towerSprite;

public:
        Tower(Game *gameInstance, int size, std::shared_ptr<std::vector<TDUnit*>> enemiesList, int cellSize, SFMLLoader &SFMLLoader);
        Tower(Game *gameInstance, int xPos, int yPos, int size, std::shared_ptr<std::vector<TDUnit*>> enemiesList);
        ~Tower() override { this->_towerThread.join(); };
        std::string getTowerName() { return (this->towerName); };
        sf::Sprite getTowerSprite() { return (this->towerSprite); };
        void removeFromEnemiesInRangeList(TDUnit *enemy) override;
        void addToEnemiesInRangeList(TDUnit *enemy) override;
        void activate(std::shared_ptr<std::vector<TDUnit*>> enemiesList) override;
        void deactivate() override;
        void fire(TDUnit *target) override;
        void isInRange() override;
        void upgrade() override;
        void setTimeBetweenAttack(float time) override;
        float getTimeBetweenAttack() override;
        int getCost(int level) override;
        int getLevel() override;
        bool isSpeedBoosted() override;
        void setSpeedBoosted(bool newSpeedBoosted) override;
        void setPosition(int posX, int posY, int cellSize) override;
        Point getPosition() override;
        bool isActivated();
        void join();
        void run(std::shared_ptr<std::vector<TDUnit*>> enemiesList) override;
        void live(std::shared_ptr<std::vector<TDUnit*>> levelEnemyList) override;
        bool isMaxed() override;
};

#endif