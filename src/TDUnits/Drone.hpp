//
// Created by adrie on 06/04/2023.
//

#ifndef UNTITLED1_DRONE_HPP
#define UNTITLED1_DRONE_HPP

#include "TDUnit.hpp"

class Drone : public TDUnit {
public:
    Drone(int posX, int posY) : TDUnit(60, 350, 0, posX, posY, false, 12, 1.3, false) {}

    virtual std::string getTypeName() {
        return "Drone";
    }
};

#endif //UNTITLED1_DRONE_HPP
