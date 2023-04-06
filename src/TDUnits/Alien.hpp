//
// Created by adrie on 06/04/2023.
//

#ifndef UNTITLED1_ALIEN_HPP
#define UNTITLED1_ALIEN_HPP

#include "TDUnit.hpp"

class Alien : public TDUnit {
public:
    Alien(int posX, int posY, SFMLLoader &sfmlLoader) : TDUnit(50, 100, 1, posX, posY, false, 10, sfmlLoader) {}

    virtual std::string getTypeName() {
        return "Alien";
    }
};

#endif //UNTITLED1_ALIEN_HPP