//
// Created by adrie on 06/04/2023.
//

#ifndef UNTITLED1_DRONE_HPP
#define UNTITLED1_DRONE_HPP

#include "TDUnit.hpp"

class Drone : public TDUnit {
public:
    Drone(int posX, int posY, SFMLLoader &sfmlLoaderUnit) : TDUnit(10, 150, 0, posX, posY, false, 12, sfmlLoaderUnit, 1.3) {}

    virtual std::string getTypeName() {
        return "Drone";
    }
};

#endif //UNTITLED1_DRONE_HPP
