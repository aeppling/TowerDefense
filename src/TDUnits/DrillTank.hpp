//
// Created by adrie on 22/05/2023.
//

#ifndef UNTITLED1_DRILLTANK_HPP
#define UNTITLED1_DRILLTANK_HPP

#include "TDUnit.hpp"

class DrillTank : public TDUnit {
public:
    DrillTank(int posX, int posY) : TDUnit(40, 400, 0, posX, posY, false, 16, 1.8, true) {}

    virtual std::string getTypeName() {
        return "DrillTank";
    }
};

#endif //UNTITLED1_DRILLTANK_HPP
