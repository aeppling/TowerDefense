//
// Created by adrie on 06/04/2023.
//

#ifndef UNTITLED1_SPACESHIP_HPP
#define UNTITLED1_SPACESHIP_HPP

#include "TDUnit.hpp"

class Spaceship : public TDUnit {
public:
    Spaceship(int posX, int posY, SFMLLoader &sfmlLoaderUnit) : TDUnit(500, 300, 10, posX, posY, false, 70, sfmlLoaderUnit) {}

    virtual std::string getTypeName() {
        return "Spaceship";
    }
};

#endif //UNTITLED1_SPACESHIP_HPP
