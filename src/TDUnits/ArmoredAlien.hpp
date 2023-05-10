//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_ARMOREDALIEN_HPP
#define UNTITLED1_ARMOREDALIEN_HPP

#include "TDUnit.hpp"

class ArmoredAlien : public TDUnit {
public:
    ArmoredAlien(int posX, int posY, SFMLLoader &sfmlLoader) : TDUnit(50, 550, 20, posX, posY, false, 17, sfmlLoader, 1.5, false) {}

    virtual std::string getTypeName() {
        return "ArmoredAlien";
    }
};

#endif //UNTITLED1_ARMOREDALIEN_HPP
