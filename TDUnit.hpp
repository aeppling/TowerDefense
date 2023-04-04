//
// Created by adrie on 17/03/2023.
//

#ifndef UNTITLED1_TDUNIT_HPP
#define UNTITLED1_TDUNIT_HPP

#include <chrono>
#include <thread>
#include "AStarPathFinding.hpp"
#include "SFMLLoader.hpp"

#include <iostream>
#include <string>

class TDUnit {
public:
    // BASICS STATS
    int _health_points;
    int _resistance;
    int _posX;
    int _posY;
    int _speed; // TIME TO TRAVEL FROM ONE CASE TO ANOTHER IN SECONDS
    bool _isFlying;
    int  _value;

    bool _alreadyCount;
    bool _alreadyArrived;

    //COORD
    int  _baseCoordX;
    int  _baseCoordY;

    // PATH FINDING AND MOVE
    std::chrono::steady_clock::time_point _timeOfLastMove; // SET WITH time(NULL) and reset at every move
    std::vector<std::shared_ptr<MapCell>> _path; // PATH TO TAKE
    std::thread                           _thread;
    TDMap                                 *_mapCopy;
    // SFML
    sf::Sprite  _sprite;
    int         _unitSize;

    // CONSTRUCTOR & OVERLOADS
    TDUnit(int hp, int speed, int resistance, int posX, int posY, bool isFlying, int value) {
        this->_health_points = hp;
        this->_speed = speed;
        this->_resistance = resistance;
        this->_posX = posX;
        this->_posY = posY;
        this->_isFlying = isFlying;
        this->_value = value;
        this->_timeOfLastMove = std::chrono::steady_clock::now();
        this->_alreadyCount = false;
        this->_alreadyArrived = false;
    }
    ~TDUnit() {
        std::cout << "Dead unit here." << std::endl;

    }
    virtual std::string getTypeName() {
        return "Enemy";
    }

    // GETTER & SETTER
    int getPosX() { return(this->_posX);}
    int getPosY() { return(this->_posY); }
    void setPosX(int posX) { this->_posX = posX; };
    void setPosY(int posY) { this->_posY = posY; };
    void setPath(std::vector<MapCell*> path);
    bool isFlying() { return (this->_isFlying); };
    int  getHealth() { return (this->_health_points); };
    void setHealth(int health) { this->_health_points = health; };
    int  getValue() { return (this->_value); };
    bool alreadyCounted() { return (this->_alreadyCount); };
    void setCounted() { this->_alreadyCount = true;};
    bool alreadyArrived() { return (this->_alreadyArrived); };
    void setAlreadyArrived() { this->_alreadyArrived = true;};

    // FUNCTIONS
    void live();
    void run(TDMap *map);
    void searchPath(std::vector<std::vector<MapCell>> *nmap, int baseCoordX, int baseCoordY);
    void move();
    bool isAtBase();
    virtual std::string getDescription() {
        std::string description = getTypeName() + " (HP: " + std::to_string(this->_health_points) + ", Resistance: " + std::to_string(this->_resistance);
        return description;
    }
    bool isBlocked(int nextPosX, int nextPosY);
    bool isAlive();
        // SFML
    void setSprite(SFMLLoader &sfmlLoader, int winSizeX, int winSizeY, int mapSizeX, int mapSizeY);
    void getShot(int damage);
    void getKill();
    sf::Sprite getSprite() {return (this->_sprite); };
};

class Goblin : public TDUnit {
public:
    Goblin(int posX, int posY) : TDUnit(50, 1500, 1, posX, posY, false, 10) {}

    virtual std::string getTypeName() {
        return "Goblin";
    }
};

class Molosse : public TDUnit {
public:
    Molosse(int posX, int posY) : TDUnit(500, 1000, 10, posX, posY, false, 20) {}

    virtual std::string getTypeName() {
        return "Molosse";
    }
};

class Golem : public TDUnit {
public:
    Golem(int posX, int posY) : TDUnit(300, 3500, 5, posX, posY, false, 40) {}

    virtual std::string getTypeName() {
        return "Golem";
    }
};

class Dragon : public TDUnit {
public:
    Dragon(int posX, int posY) : TDUnit(1000, 2000, 10, posX, posY, false, 70) {}

    virtual std::string getTypeName() {
        return "Dragon";
    }
};

class Bats : public TDUnit {
public:
    Bats(int posX, int posY) : TDUnit(20, 400, 1, posX, posY, false, 7) {}

    virtual std::string getTypeName() {
        return "Bats";
    }
};

class Minions : public TDUnit {
public:
    Minions(int posX, int posY) : TDUnit(100, 1000, 2, posX, posY, false, 15) {}

    virtual std::string getTypeName() {
        return "Minions";
    }
};

class Cowards : public TDUnit {
public:
    Cowards(int posX, int posY) : TDUnit(10, 700, 0, posX, posY, false, 12) {}

    virtual std::string getTypeName() {
        return "Cowards";
    }
};

/*
class TestUnit {
private:
    int _posX;
    int _posY;
    int _speed; // TIME TO TRAVEL FROM ONE CASE TO ANOTHER IN SECONDS
    std::chrono::steady_clock::time_point _timeOfLastMove; // SET WITH time(NULL) and reset at every move
    std::vector<MapCell*> _path; // PATH TO TAKE
    std::thread _thread;
public:
    // CONSTRUCTOR & OVERLOADS
    TestUnit(int posX, int posY);
    ~TestUnit();
    // GETTER & SETTER
    int getPosX() { return(this->_posX); }
    int getPosY() { return(this->_posY); }
    void setPosX(int posX);
    void setPosY(int posY);
    void setPath(std::vector<MapCell*> path);
    // FUNCTIONS
    void live();
    void run();
    void searchPath(std::vector<std::vector<MapCell>> *nmap, int baseCoordX, int baseCoordY);
    void move();
    bool isAtBase();
};*/

#endif //UNTITLED1_TDUNIT_HPP
