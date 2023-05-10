//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_ARMOREDREGENERATEDRONE_HPP
#define UNTITLED1_ARMOREDREGENERATEDRONE_HPP

#include "TDUnit.hpp"

class ArmoredRegenerateDrone : public TDUnit {
public:
    ArmoredRegenerateDrone(int posX, int posY, SFMLLoader &sfmlLoaderUnit) : TDUnit(400, 1000, 20, posX, posY, false, 70, sfmlLoaderUnit, 3, true) {}

    virtual std::string getTypeName() {
        return "ArmoredRegenerateDrone";
    }
};

#endif //UNTITLED1_ARMOREDREGENERATEDRONE_HPP
