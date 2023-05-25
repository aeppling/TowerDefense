//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_SFMLLOADERPLANET2_HPP
#define UNTITLED1_SFMLLOADERPLANET2_HPP

#include "SFMLLoader.hpp"

class SFMLLoaderPlanet2 : public SFMLLoader {
public:
    SFMLLoaderPlanet2() : SFMLLoader("ressources/Sprites/MyTiles/tileIce.png", "ressources/Sprites/MyTiles/tileStone.png",
                                     "ressources/Sprites/MyTiles/tileSnow_slope.png", "ressources/Sprites/MyTiles/tileSnow.png") {};
};

#endif //UNTITLED1_SFMLLOADERPLANET2_HPP
