//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_SFMLLOADERPLANET2_HPP
#define UNTITLED1_SFMLLOADERPLANET2_HPP

#include "SFMLLoader.hpp"

class SFMLLoaderPlanet2 : public SFMLLoader {
public:
    SFMLLoaderPlanet2() : SFMLLoader("Sprites/MyTiles/tileSand_slope.png", "Sprites/MyTiles/tileSand.png",
                                     "Sprites/MyTiles/tileGrass_slope.png", "Sprites/MyTiles/tileGrass.png") {};
};

#endif //UNTITLED1_SFMLLOADERPLANET2_HPP
