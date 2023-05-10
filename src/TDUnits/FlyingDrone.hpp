//
// Created by adrie on 04/05/2023.
//

#ifndef UNTITLED1_FLYINGDRONE_HPP
#define UNTITLED1_FLYINGDRONE_HPP

#include "TDUnit.hpp"

class FlyingDrone : public TDUnit {
public:
    FlyingDrone(int posX, int posY, SFMLLoader &sfmlLoaderUnit) : TDUnit(80, 300, 0, posX, posY, false, 70, sfmlLoaderUnit, 1.8, true) {}

    virtual std::string getTypeName() {
        return "FlyingDrone";
    }
};

#endif //UNTITLED1_FLYINGDRONE_HPP
