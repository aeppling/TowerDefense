//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_SFMLLOADERPLANET2_HPP
#define UNTITLED1_SFMLLOADERPLANET2_HPP

#include "SFMLLoader.hpp"

class SFMLLoaderPlanet2 : public SFMLLoader {
public:
    SFMLLoaderPlanet2() : SFMLLoader("Sprites/MyTiles/tileStone_slope.png", "Sprites/MyTiles/tileStone.png",
                                     "Sprites/MyTiles/tileSnow_slope.png", "Sprites/MyTiles/tileSnow.png") {};
};

#endif //UNTITLED1_SFMLLOADERPLANET2_HPP
