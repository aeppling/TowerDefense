//
// Created by adrie on 17/03/2023.
//

#ifndef UNTITLED1_TDUNIT_HPP
#define UNTITLED1_TDUNIT_HPP

#include <chrono>
#include <thread>
#include "../TDMap/AStarPathFinding.hpp"
#include "../TDGraphics/SFMLLoader.hpp"
#include "../TDGraphics/SFMLEnemiesLoader.hpp"

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
    int  _cellSize;
    int  _spriteSpeed; //SPRITE SPEED IN MILLISECOND PER PIXEL
    float _scale;

    // PATH FINDING AND MOVE
    std::chrono::steady_clock::time_point _timeOfLastMove; // SET WITH time(NULL) and reset at every move
    std::vector<std::shared_ptr<MapCell>> _path; // PATH TO TAKE
    std::thread                           _thread;
    TDMap                                 *_mapCopy;
    // SFML
    sf::Sprite  _sprite;
    int         _unitSize;

    // CONSTRUCTOR & OVERLOADS
    TDUnit(int hp, int speed, int resistance, int posX, int posY, bool isFlying, int value, SFMLLoader &sfmlLoaderUnit, float scale);
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
    void setSprite(SFMLEnemiesLoader &sfmlLoader, int winSizeX, int winSizeY, int mapSizeX, int mapSizeY, int cellSize);
    void getShot(int damage);
    void getKill();
    sf::Sprite getSprite() {return (this->_sprite); };
    void rotate(float posX, float posY, float destX, float destY);
};

class Molosse : public TDUnit {
public:
    Molosse(int posX, int posY, SFMLLoader &sfmlLoaderUnit) : TDUnit(500, 1000, 10, posX, posY, false, 20, sfmlLoaderUnit, 1) {}

    virtual std::string getTypeName() {
        return "Molosse";
    }
};

class Golem : public TDUnit {
public:
    Golem(int posX, int posY, SFMLLoader &sfmlLoaderUnit) : TDUnit(300, 3500, 5, posX, posY, false, 40, sfmlLoaderUnit, 1) {}

    virtual std::string getTypeName() {
        return "Golem";
    }
};

class Minions : public TDUnit {
public:
    Minions(int posX, int posY, SFMLLoader &sfmlLoaderUnit) : TDUnit(100, 1000, 2, posX, posY, false, 15, sfmlLoaderUnit, 1) {}

    virtual std::string getTypeName() {
        return "Minions";
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
