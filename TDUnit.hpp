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

    // PATH FINDING AND MOVE
    std::chrono::steady_clock::time_point _timeOfLastMove; // SET WITH time(NULL) and reset at every move
    std::vector<std::shared_ptr<MapCell>> _path; // PATH TO TAKE
    std::thread _thread;

    // SFML
    sf::Sprite  _sprite;

    // CONSTRUCTOR & OVERLOADS
    TDUnit(int hp, int speed, int resistance, int posX, int posY) {
        this->_health_points = hp;
        this->_speed = speed;
        this->_resistance = resistance;
        this->_posX = posX;
        this->_posY = posY;
        this->_timeOfLastMove = std::chrono::steady_clock::now();
    }
    ~TDUnit() {
        this->_thread.join();
    }
    virtual std::string getTypeName() {
        return "Enemy";
    }

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
    virtual std::string getDescription() {
        std::string description = getTypeName() + " (HP: " + std::to_string(this->_health_points) + ", Resistance: " + std::to_string(this->_resistance);
        return description;
    }

    // SFML
    void setSprite(SFMLLoader sfmlLoader, int winSizeX, int winSizeY, TDMap map);
};

class Goblin : public TDUnit {
public:
    Goblin(int posX, int posY) : TDUnit(50, 1500, 1, posX, posY) {}

    virtual std::string getTypeName() {
        return "Goblin";
    }
};

class Molosse : public TDUnit {
public:
    Molosse(int posX, int posY) : TDUnit(500, 1000, 10, posX, posY) {}

    virtual std::string getTypeName() {
        return "Molosse";
    }
};

class Golem : public TDUnit {
public:
    Golem(int posX, int posY) : TDUnit(300, 3500, 5, posX, posY) {}

    virtual std::string getTypeName() {
        return "Golem";
    }
};

class Dragon : public TDUnit {
public:
    Dragon(int posX, int posY) : TDUnit(1000, 2000, 10, posX, posY) {}

    virtual std::string getTypeName() {
        return "Dragon";
    }
};

class Bats : public TDUnit {
public:
    Bats(int posX, int posY) : TDUnit(20, 400, 1, posX, posY) {}

    virtual std::string getTypeName() {
        return "Bats";
    }
};

class Minions : public TDUnit {
public:
    Minions(int posX, int posY) : TDUnit(100, 1000, 2, posX, posY) {}

    virtual std::string getTypeName() {
        return "Minions";
    }
};

class Cowards : public TDUnit {
public:
    Cowards(int posX, int posY) : TDUnit(10, 700, 0, posX, posY) {}

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
