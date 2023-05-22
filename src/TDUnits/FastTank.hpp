//
// Created by adrie on 22/05/2023.
//

#ifndef UNTITLED1_FASTTANK_HPP
#define UNTITLED1_FASTTANK_HPP

#include "TDUnit.hpp"

class FastTank : public TDUnit {
public:
    FastTank(int posX, int posY) : TDUnit(80, 300, 0, posX, posY, false, 22, 2, false) {}

    virtual std::string getTypeName() {
        return "FastTank";
    }
};

#endif //UNTITLED1_FASTTANK_HPP
