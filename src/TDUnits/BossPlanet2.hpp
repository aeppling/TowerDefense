//
// Created by adrie on 16/05/2023.
//

#ifndef UNTITLED1_BOSSPLANET2_HPP
#define UNTITLED1_BOSSPLANET2_HPP

#include "TDUnit.hpp"

class BossPlanet2 : public TDUnit {
public:
    BossPlanet2(int posX, int posY) : TDUnit(500, 1000, 0, posX, posY, false, 70, 1.8, false) {}

    virtual std::string getTypeName() {
        return "BossPlanet2";
    }
};

#endif //UNTITLED1_BOSSPLANET2_HPP
