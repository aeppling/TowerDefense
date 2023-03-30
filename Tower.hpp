#ifndef TOWER_HPP_
#define TOWER_HPP_

#include "TDUnit.hpp"
#include "Game.hpp"
#include "usefullStruct.hpp"

#include <vector>
#include <thread>
#include <algorithm> 

class Game;

class Tower{
    //* Basic parent tower Class
    protected:
        //Game gameInstance;
        Point size;
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
        Tower(Game *gameInstance);
        Tower(Game *gameInstance, int xPos, int yPos);
        ~Tower() { this->_towerThread.join(); };
        void removeFromEnemiesInRangeList(TDUnit *enemy);
        void addToEnemiesInRangeList(TDUnit *enemy);
        void activate(std::vector<TDUnit *> &enemiesList);
        void deactivate();
        void fire(TDUnit *target);
        void isInRange(std::vector<TDUnit *> &enemiesList);
        void upgrade();
        void setTimeBetweenAttack(float time);
        float getTimeBetweenAttack();
        int getCost(int level);
        int getLevel();
        bool isSpeedBoosted();
        void setSpeedBoosted(bool newSpeedBoosted);
        void setPosition(int posX, int posY);
        Point getPosition();
        Point getSize();
        void run(std::vector<TDUnit *> &enemiesList);
        void live(std::vector<std::vector<TDUnit*>> &levelEnemyList, int *waveNumber);
        bool isMaxed();
};

#endif