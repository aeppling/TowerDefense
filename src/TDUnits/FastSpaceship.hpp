//
// Created by adrie on 22/05/2023.
//

#ifndef UNTITLED1_FASTSPACESHIP_HPP
#define UNTITLED1_FASTSPACESHIP_HPP

#include "TDUnit.hpp"

class FastSpaceship : public TDUnit {
public:
    FastSpaceship(int posX, int posY) : TDUnit(60, 400, 0, posX, posY, true, 40, 2.5, false) {}

    virtual std::string getTypeName() {
        return "FastSpaceship";
    }
};

#endif //UNTITLED1_FASTSPACESHIP_HPP
