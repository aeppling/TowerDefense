//
// Created by adrie on 06/04/2023.
//

#ifndef UNTITLED1_MISSILE_HPP
#define UNTITLED1_MISSILE_HPP

#include "TDUnit.hpp"

class Missile : public TDUnit {
public:
    Missile(int posX, int posY) : TDUnit(5, 100, 0, posX, posY, false, 7, 1, true) {}

    virtual std::string getTypeName() {
        return "Missile";
    }
};

#endif //UNTITLED1_MISSILE_HPP
