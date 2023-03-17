//
// Created by adrie on 17/03/2023.
//

#ifndef UNTITLED1_TESTUNIT_HPP
#define UNTITLED1_TESTUNIT_HPP

#include <chrono>
#include "AStarPathFinding.hpp"

class TestUnit {
private:
    int _posX;
    int _posY;
    int _speed; // TIME TO TRAVEL FROM ONE CASE TO ANOTHER IN SECONDS
    std::chrono::steady_clock::time_point _timeOfLastMove; // SET WITH time(NULL) and reset at every move
    std::vector<MapCell*> _path; // PATH TO TAKE
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
    void searchPath(std::vector<std::vector<MapCell>> *nmap, int baseCoordX, int baseCoordY);
    void move();
    bool isAtBase();
};

#endif //UNTITLED1_TESTUNIT_HPP
