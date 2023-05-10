//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_ARMOREDDRONE_HPP
#define UNTITLED1_ARMOREDDRONE_HPP

#include "TDUnit.hpp"

class ArmoredDrone : public TDUnit {
public:
    ArmoredDrone(int posX, int posY, SFMLLoader &sfmlLoaderUnit) : TDUnit(20, 350, 20, posX, posY, false, 12, sfmlLoaderUnit, 1.3, false) {}

    virtual std::string getTypeName() {
        return "ArmoredDrone";
    }
};

#endif //UNTITLED1_ARMOREDDRONE_HPP
