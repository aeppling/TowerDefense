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
        std::vector<TDUnit *> enemiesList;
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

    public:
        Tower(Game *gameInstance, int size);
        Tower(Game *gameInstance, int xPos, int yPos, int size);
        ~Tower() override { this->_towerThread.join(); };
        void removeFromEnemiesInRangeList(TDUnit *enemy) override;
        void addToEnemiesInRangeList(TDUnit *enemy) override;
        void activate(std::vector<TDUnit *> &enemiesList) override;
        void deactivate() override;
        void fire(TDUnit *target) override;
        void isInRange(std::vector<TDUnit *> &enemiesList) override;
        void upgrade() override;
        void setTimeBetweenAttack(float time) override;
        float getTimeBetweenAttack() override;
        int getCost(int level) override;
        int getLevel() override;
        bool isSpeedBoosted() override;
        void setSpeedBoosted(bool newSpeedBoosted) override;
        void setPosition(int posX, int posY) override;
        Point getPosition() override;
        void run(std::vector<TDUnit *> &enemiesList) override;
        void live(std::vector<std::vector<TDUnit*>> &levelEnemyList, int *waveNumber) override;
        bool isMaxed() override;
};

#endif