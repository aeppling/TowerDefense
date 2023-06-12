//
// Created by adrie on 16/05/2023.
//

#ifndef UNTITLED1_BOSSPLANET1_HPP
#define UNTITLED1_BOSSPLANET1_HPP

#include "TDUnit.hpp"

class BossPlanet1 : public TDUnit {
public:
    BossPlanet1(int posX, int posY) : TDUnit(2500, 1500, 10, posX, posY, false, 70, 2.3, false) {}

    virtual std::string getTypeName() {
        return "BossPlanet1";
    }
};

#endif //UNTITLED1_BOSSPLANET1_HPP
