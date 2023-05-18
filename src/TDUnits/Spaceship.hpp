//
// Created by adrie on 06/04/2023.
//

#ifndef UNTITLED1_SPACESHIP_HPP
#define UNTITLED1_SPACESHIP_HPP

#include "TDUnit.hpp"

class Spaceship : public TDUnit {
public:
    Spaceship(int posX, int posY) : TDUnit(120, 750, 0, posX, posY, true, 70, 3.5, false) {}

    virtual std::string getTypeName() {
        return "Spaceship";
    }
};

#endif //UNTITLED1_SPACESHIP_HPP
