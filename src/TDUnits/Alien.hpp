//
// Created by adrie on 06/04/2023.
//

#ifndef UNTITLED1_ALIEN_HPP
#define UNTITLED1_ALIEN_HPP

#include "TDUnit.hpp"

class Alien : public TDUnit {
public:
    Alien(int posX, int posY) : TDUnit(50, 550, 0, posX, posY, false, 17, 1.5, false) {}

    virtual std::string getTypeName() {
        return "Alien";
    }
};

#endif //UNTITLED1_ALIEN_HPP
