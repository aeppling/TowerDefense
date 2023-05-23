//
// Created by adrie on 22/05/2023.
//

#ifndef UNTITLED1_CROSSTANK_HPP
#define UNTITLED1_CROSSTANK_HPP

#include "TDUnit.hpp"

class CrossTank : public TDUnit {
public:
    CrossTank(int posX, int posY) : TDUnit(110, 550, 0, posX, posY, false, 20, 2, false) {}

    virtual std::string getTypeName() {
        return "CrossTank";
    }
};

#endif //UNTITLED1_CROSSTANK_HPP
