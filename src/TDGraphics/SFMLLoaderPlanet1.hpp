//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_SFMLLOADERPLANET1_HPP
#define UNTITLED1_SFMLLOADERPLANET1_HPP

#include "SFMLLoader.hpp"

class SFMLLoaderPlanet1 : public SFMLLoader {
public:
    SFMLLoaderPlanet1() : SFMLLoader("Sprites/MyTiles/tileSand_slope.png", "Sprites/MyTiles/tileSand.png",
                                                        "Sprites/MyTiles/tileGrass_slope.png", "Sprites/MyTiles/tileGrass.png") {};
};

#endif //UNTITLED1_SFMLLOADERPLANET1_HPP
