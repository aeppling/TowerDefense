//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_ARMOREDFLYINGDRONE_HPP
#define UNTITLED1_ARMOREDFLYINGDRONE_HPP

#include "TDUnit.hpp"

class ArmoredFlyingDrone : public TDUnit {
public:
    ArmoredFlyingDrone(int posX, int posY, SFMLLoader &sfmlLoaderUnit) : TDUnit(80, 300, 20, posX, posY, false, 70, sfmlLoaderUnit, 1.8, true) {}

    virtual std::string getTypeName() {
        return "ArmoredFlyingDrone";
    }
};

#endif //UNTITLED1_ARMOREDFLYINGDRONE_HPP