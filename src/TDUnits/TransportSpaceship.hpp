//
// Created by adrie on 22/05/2023.
//

#ifndef UNTITLED1_TRANSPORTSPACESHIP_HPP
#define UNTITLED1_TRANSPORTSPACESHIP_HPP

#include "TDUnit.hpp"

class TransportSpaceship : public TDUnit {
public:
    TransportSpaceship(int posX, int posY) : TDUnit(1500, 1200, 0, posX, posY, true, 180, 3.5, false) {}

    virtual std::string getTypeName() {
        return "TransportSpaceship";
    }
};

#endif //UNTITLED1_TRANSPORTSPACESHIP_HPP
