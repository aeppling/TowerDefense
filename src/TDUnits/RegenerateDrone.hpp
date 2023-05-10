//
// Created by adrie on 06/05/2023.
//

#ifndef UNTITLED1_REGENERATEDRONE_HPP
#define UNTITLED1_REGENERATEDRONE_HPP

#include "TDUnit.hpp"

class RegenerateDrone : public TDUnit {
public:
    RegenerateDrone(int posX, int posY, SFMLLoader &sfmlLoaderUnit) : TDUnit(400, 1000, 0, posX, posY, false, 70, sfmlLoaderUnit, 3, true) {}

    virtual std::string getTypeName() {
        return "RegenerateDrone";
    }
};
#endif //UNTITLED1_REGENERATEDRONE_HPP
