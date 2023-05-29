//
// Created by adrie on 16/05/2023.
//

#ifndef UNTITLED1_BOSSPLANET2_HPP
#define UNTITLED1_BOSSPLANET2_HPP

#include "TDUnit.hpp"

class BossPlanet2 : public TDUnit {
public:
    BossPlanet2(int posX, int posY) : TDUnit(3000, 1500, 30, posX, posY, false, 70, 2.6, false) {}

    virtual std::string getTypeName() {
        return "BossPlanet2";
    }
};

#endif //UNTITLED1_BOSSPLANET2_HPP
