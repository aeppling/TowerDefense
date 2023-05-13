//
// Created by adrie on 13/05/2023.
//

#ifndef UNTITLED1_ARMOREDALIEN_HPP
#define UNTITLED1_ARMOREDALIEN_HPP

#include "TDUnit.hpp"

class ArmoredAlien : public TDUnit {
public:
    ArmoredAlien(int posX, int posY) : TDUnit(50, 550, 25, posX, posY, false, 17, 1.5, false) {}

    virtual std::string getTypeName() {
        return "ArmoredAlien";
    }
};

#endif //UNTITLED1_ARMOREDALIEN_HPP
