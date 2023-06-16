//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_ARMOREDFLYINGDRONE_HPP
#define UNTITLED1_ARMOREDFLYINGDRONE_HPP

#include "TDUnit.hpp"

class ArmoredFlyingDrone : public TDUnit {
public:
    ArmoredFlyingDrone(int posX, int posY) : TDUnit(200, 800, 66, posX, posY, false, 70, 1.8, true) {}

    virtual std::string getTypeName() {
        return "ArmoredFlyingDrone";
    }
};

#endif //UNTITLED1_ARMOREDFLYINGDRONE_HPP
