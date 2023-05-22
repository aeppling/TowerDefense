//
// Created by adrie on 22/05/2023.
//

#ifndef UNTITLED1_TANK_HPP
#define UNTITLED1_TANK_HPP

#include "TDUnit.hpp"

class Tank : public TDUnit {
public:
    Tank(int posX, int posY) : TDUnit(120, 500, 0, posX, posY, false, 27, 2.3, false) {}

    virtual std::string getTypeName() {
        return "Tank";
    }
};

#endif //UNTITLED1_TANK_HPP
