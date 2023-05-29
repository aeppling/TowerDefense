//
// Created by adrie on 16/05/2023.
//

#ifndef UNTITLED1_BOSSPLANET3_HPP
#define UNTITLED1_BOSSPLANET3_HPP

#include "TDUnit.hpp"

class BossPlanet3 : public TDUnit {
public:
    BossPlanet3(int posX, int posY) : TDUnit(2500, 1000, 70, posX, posY, false, 70, 2.5, false) {}

    virtual std::string getTypeName() {
        return "BossPlanet3";
    }
};

#endif //UNTITLED1_BOSSPLANET3_HPP
