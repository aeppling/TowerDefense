//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_SFMLLOADERPLANET1_HPP
#define UNTITLED1_SFMLLOADERPLANET1_HPP

#include "SFMLLoader.hpp"

class SFMLLoaderPlanet1 : public SFMLLoader {
public:
    SFMLLoaderPlanet1() : SFMLLoader("ressources/Sprites/MyTiles/tileSand_slope.png", "ressources/Sprites/MyTiles/tileSand.png",
                                                        "ressources/Sprites/MyTiles/tileGrass_slope.png", "ressources/Sprites/MyTiles/tileGrass.png") {};
};

#endif //UNTITLED1_SFMLLOADERPLANET1_HPP
