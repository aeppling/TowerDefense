//
// Created by adrie on 10/05/2023.
//

#ifndef UNTITLED1_SFMLLOADERPLANET3_HPP
#define UNTITLED1_SFMLLOADERPLANET3_HPP

#include "SFMLLoader.hpp"

class SFMLLoaderPlanet3 : public SFMLLoader {
public:
    SFMLLoaderPlanet3() : SFMLLoader("ressources/Sprites/MyTiles/tileSpawnCell.png", "ressources/Sprites/MyTiles/SpawnCellHeight.png",
                                     "ressources/Sprites/MyTiles/tileGoo_slope.png", "ressources/Sprites/MyTiles/tileGoo.png") {};
};

#endif //UNTITLED1_SFMLLOADERPLANET3_HPP
