//
// Created by adrie on 16/05/2023.
//

#ifndef UNTITLED1_BOSSPLANET3_HPP
#define UNTITLED1_BOSSPLANET3_HPP

#include "TDUnit.hpp"

class BossPlanet3 : public TDUnit {
public:
    BossPlanet3(int posX, int posY) : TDUnit(500, 1000, 0, posX, posY, false, 70, 1.8, false) {}

    virtual std::string getTypeName() {
        return "BossPlanet3";
    }
};

#endif //UNTITLED1_BOSSPLANET3_HPP
