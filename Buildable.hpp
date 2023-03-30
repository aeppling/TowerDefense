//
// Created by adrie on 30/03/2023.
//

#ifndef UNTITLED1_BUILDABLE_HPP
#define UNTITLED1_BUILDABLE_HPP

class Buildable {
private:
    int         _size;
    std::string _type;
public:
    Buildable(int size, std::string type) : _size(size), _type(type) {};
    virtual ~Buildable() {};

    // GETTER & SETTER
    int getSize() { return(this->_size); };
    void setSize(int size) { this->_size = size; };
    std::string getType() { return(this->_type); };

    // VIRTUAL TOWER FUNCTIONS
    virtual void removeFromEnemiesInRangeList(TDUnit *enemy) = 0;
    virtual void addToEnemiesInRangeList(TDUnit *enemy) = 0;
    virtual void activate(std::vector<TDUnit *> &enemiesList) = 0;
    virtual void deactivate() = 0;
    virtual void fire(TDUnit *target) = 0;
    virtual void isInRange(std::vector<TDUnit *> &enemiesList) = 0;
    virtual void upgrade() = 0;
    virtual void setTimeBetweenAttack(float time) = 0;
    virtual float getTimeBetweenAttack() = 0;
    virtual int getCost(int level) = 0;
    virtual int getLevel() = 0;
    virtual bool isSpeedBoosted() = 0;
    virtual void setSpeedBoosted(bool newSpeedBoosted) = 0;
    virtual void setPosition(int posX, int posY) = 0;
    virtual Point getPosition() = 0;
    virtual void run(std::vector<TDUnit *> &enemiesList) = 0;
    virtual void live(std::vector<std::vector<TDUnit*>> &levelEnemyList, int *waveNumber) = 0;
    virtual bool isMaxed() = 0;
};

#endif //UNTITLED1_BUILDABLE_HPP